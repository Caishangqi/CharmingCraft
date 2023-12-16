// Copyright Epic Games, Inc. All Rights Reserved.


#include "CharmingCraftGameModeBase.h"

#include "Object/Class/Core/CharmingCraftInstance.h"

APawn* ACharmingCraftGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	// 你可以在这里加入自定义逻辑来决定如何生成Pawn
	// 例如，使用GameInstance中存储的玩家信息
	TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(GetGameInstance());
	// 确保StartSpot是有效的PlayerStart
	if (StartSpot && GameInstance->PlayerCharacter)
	{
		// 创建你的自定义Pawn
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		FVector Location = StartSpot->GetActorLocation();
		FRotator Rotation = StartSpot->GetActorRotation();

		// 假设YourCharacterClass是你的玩家角色类
		TObjectPtr<ADCharacter> PlayerCharacter = GetWorld()->SpawnActor<ADCharacter>(
			ADCharacter::StaticClass(), Location, Rotation, SpawnParams);
		PlayerCharacter->InventoryComponent = GameInstance->PlayerCharacter->InventoryComponent;
		return PlayerCharacter;
	}
	return nullptr;
}
