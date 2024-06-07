// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWorldStaticLibarary.h"

#include "CharmingCraft/Core/World/NativeCraftWorld.h"
#include "GameFramework/Character.h"

UNativeCraftWorld* UCraftWorldStaticLibarary::TeleportPlayerToWorld(ACharacter* PlayerCharacter, FString WorldName,
                                                                    UNativeCraftWorld* TargetWorld)
{
	TargetWorld->OnCraftWorldPrepareInternal.AddLambda([PlayerCharacter,WorldName,TargetWorld]
	{
		GetWorldHandler(PlayerCharacter)->TeleportPlayerToWorld_Internal(PlayerCharacter, WorldName, TargetWorld);
		TargetWorld->OnCraftWorldPrepareInternal.Clear();
		UGameplayStatics::GetPlayerCameraManager(PlayerCharacter, 0)->StopCameraFade();
		PlayerCharacter->SetActorHiddenInGame(false);
	});
	GetWorldHandler(PlayerCharacter)->ShownCraftWorld(TargetWorld);
	return TargetWorld;
}
