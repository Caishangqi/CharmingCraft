// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "../Core/Interact/Interface/DGameplayInterface.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "NativeInteractActor.generated.h"


/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API ANativeInteractActor : public AActor, public IMouseInteractInterface, public ICoreManagerInterface
{
	GENERATED_BODY()

	/* 属性 */
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	int32 MinimumInteractRange; //Can beautiful handle in Enumeration

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	bool bIgnoreRangeToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	bool bIsAllowToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	bool bIsAllowToDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visiability")
	bool bIsHighlighted;

	/* 蓝图类,存放点击高亮的蓝图CLass,利用反射获取这个Class */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	TSubclassOf<UActorComponent> BlueprintComponentClass;

	/* 点击组件,这个组件是  BlueprintComponentClass 的实例对象,只能在BeginPlay()注册*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction")
	UActorComponent* ClickableComponent;

	/* 方法 */
	ANativeInteractActor();
	
	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;

	virtual void BeginPlay() override;


	void FindClassBaseOnBluePrint();

	void RegisterComponent();
};
