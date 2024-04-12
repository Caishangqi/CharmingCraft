// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHolder.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

UUserWidgetEventHandler* UWidgetHolder::GetWidgetHolder()
{
	return UserWidgetEventHandler;
}

UObject* UWidgetHolder::GetCreator()
{
	return Creator;
}

bool UWidgetHolder::RemoveWidget_Implementation()
{
	bool bIsRemoveLeastOne = false;
	for (auto& UserWidget : UserWidgetEventHandler->LoadedUserWidget)
	{
		if (this == UserWidget)
		{
			UserWidgetEventHandler->LoadedUserWidget.Remove(this);
			UE_LOG(LogChamingCraftWidgetHandler, Display,
			       TEXT("[❌]  Remove Widget: %s from Widget Event Handler(Holder)"), *this->GetName());
			bIsRemoveLeastOne = true;
		}
	}
	return bIsRemoveLeastOne;
}

void UWidgetHolder::NativeConstruct()
{
	Super::NativeConstruct();
	MaxInstanceOfWidget = 1;
	GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	UserWidgetEventHandler = GameInstance->GetUserWidgetEventHandler();
	UE_LOG(LogChamingCraftWidgetHandler, Display,
	       TEXT("[✅]  Add Widget: %s to Widget Event Handler(Holder)"), *this->GetName());
	UserWidgetEventHandler->LoadedUserWidget.Push(this);
}

void UWidgetHolder::NativeDestruct()
{
	Super::NativeDestruct();
	RemoveWidget_Implementation();
}
