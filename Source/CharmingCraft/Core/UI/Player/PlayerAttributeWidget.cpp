// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeWidget.h"

#include "../Core/Entity/Player/NativePlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UPlayerAttributeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPlayerAttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 获取玩家角色引用
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		ANativePlayerCharacter* Character = Cast<ANativePlayerCharacter>(PlayerController->GetPawn());
		if (Character)
		{
			Player = Character;
			// 在这里可以进行更多的初始化工作，比如使用Player变量更新UI元素等
		}
	}
}
