// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "CharmingCraft/Core/GameInstance/Interface/CoreManagerInterface.h"
#include "CharmingCraft/Core/Item/Meta/ItemMeta.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "Components/ActorComponent.h"
#include "EquipmentSkill/ItemDynamicSkill.h"
#include "Templates/Tuple.h"
#include "CraftActionComponent.generated.h"

/*
 *	Action Component Holds the actions we want to able to use
 *	The main goal of Action Component is to keep a list of actions
 */

class UItemActionComponent;
class UNativeAction;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API UCraftActionComponent : public UActorComponent, public IGameplayTagAssetInterface,
                                            public ICoreManagerInterface
{
	GENERATED_BODY()

public:
	/*
	 *	GameTag System
	 *	We can not use forwards declaration because it is a struct and
	 *	the compiler need to know the size of the struct, if it is a   
	 *	pointer(same size) it do not need to know
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Tags")
	FGameplayTagContainer ActiveGamePlayTags;

	UFUNCTION(BlueprintCallable, Category= "Actions")
	void AddAction(TSubclassOf<UNativeAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	void AddBindAction(int32 index, TSubclassOf<UNativeAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool AddItemDynamicSkills(UItemMeta* ItemMeta);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool RemoveItemDynamicSkills(UItemMeta* ItemMeta);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StartActionByName(APawn* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StartActionByType(APawn* Instigator, EItemDynamicSkillSlot ActionType);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StopActionByType(APawn* Instigator, EItemDynamicSkillSlot ActionType);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool HasActionByType(EItemDynamicSkillSlot ActionType);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	void OnItemDynamicSkillBindEvent(APawn* Instigator, UNativeAction* FromAction, UNativeAction* TargetAction,
	                                 UItemMeta* ContextMeta);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StartActionByIndex(APawn* Instigator, int32 index);

	UFUNCTION(BlueprintCallable, Category= "Actions")
	bool StopActionByName(APawn* Instigator, FName ActionName);
	
	bool MappingItemActionToComponent(UItemActionComponent * ItemActionComponent, bool bSetToRemoveMapping = false);

	UFUNCTION(BlueprintCallable, Category= "Cast")
	void CastActionOne();

	// Sets default values for this component's properties
	UCraftActionComponent();

	/** Granted abilities at game start */
	UPROPERTY(EditAnywhere, Category = "Editor Actions")
	TArray<TSubclassOf<UNativeAction>> DefaultActions;

	/* EDITOR ONLY: Default bind Action */
	UPROPERTY(EditAnywhere, Category = "Editor Actions")
	TMap<int32, TSubclassOf<UNativeAction>> DefaultBindAction;

	// List of actions
	UPROPERTY(BlueprintReadWrite) // When we deal with pointers to actions, we want to let UE handle
	TArray<UNativeAction*> Actions;

	/* Bind Action for example q - Action1 */
	UPROPERTY(EditAnywhere, Category = "Actions", BlueprintReadWrite)
	TMap<int32, TObjectPtr<UNativeAction>> BindAction;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	UFUNCTION()
	void OnActorOnEquipmentEvent(UObject* Instigator, UItemStack*
	                             OnEquipItem, int32 EquipIndex);
	UFUNCTION()
	void OnActorUnEquipmentEvent(UObject * Instigator, UItemStack *
											   UnEquipItem, int32 EquipIndex);

	virtual UCharmingCraftInstance* GetGameInstance_Implementation() override;
	virtual UGameEventHandler* GetGameEventHandler_Implementation() override;
	virtual UWorldManager* GetWorldManager_Implementation() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
};
