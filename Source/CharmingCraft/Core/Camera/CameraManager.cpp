// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "GameFramework/SpringArmComponent.h"

class UCameraComponent;

UCameraManager::UCameraManager()
{
	// Load the DataTable using its path
	static ConstructorHelpers::FObjectFinder<UDataTable> CameraPerspectiveDataTableFinder(
		TEXT("DataTable'/Game/CharmingCraft/Camera/DT_CameraPerspective.DT_CameraPerspective'"));
	if (CameraPerspectiveDataTableFinder.Succeeded())
	{
		UE_LOG(LogChamingCraftAsset, Display,
		       TEXT("[📁]  Success Loaded Asset :%s"), *CameraPerspectiveDataTableFinder.Object.GetName());
		LoadedCameraPerspective = CameraPerspectiveDataTableFinder.Object;
	}
}

bool UCameraManager::SwitchPlayerCameraView(APawn* Player, ECameraPerspectiveEnum TargetCameraPerspectiveEnum)
{
	if (!LoadedCameraPerspective)
	{
		UE_LOG(LogTemp, Warning, TEXT("Data table is not loaded."));
		return false;
	}

	// 用来存储查找结果的指针
	FCameraPerspective* CameraPerspective = nullptr;

	// 遍历数据表查找对应的摄像机视角
	static const FString ContextString(TEXT("GENERAL"));
	for (auto It = LoadedCameraPerspective->GetRowMap().CreateConstIterator(); It; ++It)
	{
		FCameraPerspective* Row = reinterpret_cast<FCameraPerspective*>(It.Value());
		if (Row && Row->CameraPerspectiveName == TargetCameraPerspectiveEnum)
		{
			CameraPerspective = Row;
			break;
		}
	}

	// 如果找到了相应的行
	if (CameraPerspective)
	{
		TObjectPtr<ANativePlayerCharacter> PlayerCharacter = Player ? Cast<ANativePlayerCharacter>(Player) : nullptr;
		if (PlayerCharacter)
		{
			// 获取摄像机组件
			TObjectPtr<UCameraComponent> CameraComponent = PlayerCharacter->CameraComp;
			TObjectPtr<USpringArmComponent> SpringArmComponent = PlayerCharacter->SpringArmComp;
			
			if (CameraComponent)
			{
				// 设置摄像机参数
				CameraComponent->SetRelativeLocation(CameraPerspective->Location);
				CameraComponent->SetRelativeRotation(CameraPerspective->Rotation);
				if (CameraPerspective->FieldOfView != 0)
				{
					CameraComponent->FieldOfView = CameraPerspective->FieldOfView;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Camera Component found on player"));
			}
			if (SpringArmComponent)
			{
				SpringArmComponent->SetRelativeLocation(CameraPerspective->SpringLocation);
				SpringArmComponent->SetRelativeRotation(CameraPerspective->SpringRotation);
				UE_LOG(LogTemp, Warning, TEXT("Spring Arm Component has been set"));
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Spring Arm Component found on player."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player controller or pawn is not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No matching camera perspective found in data table."));
	}

	return false;
}
