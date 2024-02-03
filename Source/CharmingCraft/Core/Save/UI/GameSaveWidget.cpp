// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveWidget.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Save/GameSaveManager.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"




void UGameSaveWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UE_LOG(LogChamingCraftSave, Display, TEXT("[!] SaveSystem Widget PreConstruct"));


	// 获取GameInstance
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		// 获取SaveManager实例
		SaveManager = GameInstance->GetSaveManager();
		UE_LOG(LogChamingCraftSave, Display, TEXT("[+] SaveSystem Widget Set SaveManager"));
		// 现在你可以使用SaveManager进行操作
	}
}
