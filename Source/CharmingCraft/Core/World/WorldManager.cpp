// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "Kismet/GameplayStatics.h"

bool UWorldManager::LoadGameLevel(FName LevelName)

{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OnLevelLoadedCallback";
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	if (UGameplayStatics::GetCurrentLevelName(this, true) == "PersistentLevel")
	{
		// 异步加载关卡
		UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, LatentInfo);
		return false;
	}
	UGameplayStatics::OpenLevel(this, FName("L_PersistentLevel"));
	// 异步加载关卡
	UGameplayStatics::LoadStreamLevel(this, LevelName, true, true, LatentInfo);
	return true;
}

bool UWorldManager::TeleportPlayerToWorld(APawn* PlayerCharacter, UWorld* TargetWorld, const FName WarpPoint)
{
	if (PlayerCharacter && TargetWorld)
	{
		if (PlayerCharacter->GetWorld() == TargetWorld)
		{
			return false;
		}
		UGameplayStatics::OpenLevelBySoftObjectPtr(PlayerCharacter,TargetWorld);
		if (true)
		{
			
		}
	}
	return false;
}

void UWorldManager::OnLevelLoadedCallback()
{
	OnLevelLoaded.Broadcast();
}
