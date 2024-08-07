// Fill out your copyright notice in the Description page of Project Settings.


#include "../Core/Interact/NativeInteractActor.h"
#include "Kismet/GameplayStatics.h"

ANativeInteractActor::ANativeInteractActor()
{
	MinimumInteractRange = 250;
	bIgnoreRangeToInteract = false;
	bIsAllowToInteract = true;
	bIsHighlighted = true;
	FindClassBaseOnBluePrint();
}

UCharmingCraftInstance* ANativeInteractActor::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UWorldManager* ANativeInteractActor::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}

UGameEventHandler* ANativeInteractActor::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}


void ANativeInteractActor::BeginPlay()
{
	Super::BeginPlay();
	if (bIsHighlighted)
	{
		RegisterComponent();
	}
}

/*!
 *
 *	基于加载的蓝图类来找到该蓝图类对应的 C++ 的Class, 注意UE编辑器创作的蓝图
 *	也就是Context内的蓝图在编译的时候就加载了,其他模块的蓝图和插件生成的蓝图会
 *	在UE编辑器运行的时候加载, 因此构造器中无法获得这个蓝图
 *	@return void 
 */

void ANativeInteractActor::FindClassBaseOnBluePrint()
{
	static ConstructorHelpers::FClassFinder<UActorComponent> BlueprintComponentFinder(
		TEXT(
			"/Game/CharmingCraft/Objects/Components/DClickableActionComponentBP"));
	BlueprintComponentClass = BlueprintComponentFinder.Class;
}

/*!
 * 在注册完蓝图类后,基于这个模板类型注册组件
 * @return	void
 */
void ANativeInteractActor::RegisterComponent()
{
	if (BlueprintComponentClass != nullptr)
	{
		ClickableComponent = NewObject<UActorComponent>(this, BlueprintComponentClass);
		if (ClickableComponent != nullptr)
		{
			ClickableComponent->RegisterComponent();
		}
	}
}
