// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHolder.h"

#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/CharmingCraftInstance.h"
#include "Kismet/GameplayStatics.h"

UNativeUserWidgetEventHandler* UWidgetHolder::GetWidgetHolder()
{
	return UserWidgetEventHandler;
}

UObject* UWidgetHolder::GetCreator()
{
	return Creator;
}

void UWidgetHolder::OnOpenWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
}


void UWidgetHolder::OnCloseWidgetEvent_Implementation(UObject* Instigator, UUserWidget* TargetWidget)
{
}

bool UWidgetHolder::RemoveWidget_Implementation()
{
	bool bIsRemoveLeastOne = false;
	TArray<UUserWidget*> WidgetsToRemove;

	for (auto UserWidget : UserWidgetEventHandler->LoadedUserWidget)
	{
		if (this == UserWidget)
		{
			// Broadcase the event from game event handler
			GameInstance->GetGameEventHandler()->OnCloseWidgetEvent(UserWidgetEventHandler, this);
			WidgetsToRemove.Add(this);
			UE_LOG(LogChamingCraftWidgetHandler, Display,
			       TEXT("[❌]  Remove Widget <%s> from Widget Event Handler(Holder)"), *this->GetName());
			bIsRemoveLeastOne = true;
		}
	}

	for (auto& Widget : WidgetsToRemove)
	{
		UserWidgetEventHandler->LoadedUserWidget.Remove(Widget);
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
	       TEXT("[✅]  Add Widget <%s> to Widget Event Handler(Holder)"), *this->GetName());

	// 先解绑之前的绑定
	GameInstance->GetGameEventHandler()->OnOpenWidget.RemoveAll(this);
	GameInstance->GetGameEventHandler()->OnCloseWidget.RemoveAll(this);

	// 再进行绑定
	GameInstance->GetGameEventHandler()->OnOpenWidget.AddDynamic(this, &UWidgetHolder::OnOpenWidgetEvent);
	GameInstance->GetGameEventHandler()->OnCloseWidget.AddDynamic(this, &UWidgetHolder::OnCloseWidgetEvent);
	UserWidgetEventHandler->LoadedUserWidget.Push(this);

	// Broadcase open widget event target is self
	GameInstance->GetGameEventHandler()->OnOpenWidgetEvent(UserWidgetEventHandler, this);
}


void UWidgetHolder::NativeDestruct()
{
	Super::NativeDestruct();
	// Automatically run RemoveWidget()
	RemoveWidget_Implementation();
}

UCharmingCraftInstance* UWidgetHolder::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* UWidgetHolder::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
