// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
#include "CameraManager.generated.h"

UENUM(BlueprintType)
enum class ECameraPerspectiveEnum : uint8
{
	INCLINE,
	VERTICAL
};


USTRUCT(BlueprintType)
struct FCameraPerspective : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	ECameraPerspectiveEnum CameraPerspectiveName;

	// 摄像机的位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	FVector Location;

	// 摄像机的旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	FRotator Rotation;

	// 摄像机的视野角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float FieldOfView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	FVector SpringLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	FRotator SpringRotation;

public:
	FCameraPerspective(): CameraPerspectiveName(ECameraPerspectiveEnum::INCLINE), Location(FVector()),
	                      Rotation(FRotator()), FieldOfView(0), SpringLocation(FVector()), SpringRotation(FRotator())
	{
	}
};

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UCameraManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CameraPerspective")
	TObjectPtr<UDataTable> LoadedCameraPerspective;

public:
	UCameraManager();

	UFUNCTION(BlueprintCallable)
	bool SwitchPlayerCameraView(APawn* Player, ECameraPerspectiveEnum TargetCameraPerspectiveEnum);
};
