// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Data/PersistentDataContainer.h"
#include "CharmingCraft/Core/Skill/EquipmentSkill/ItemDynamicSkill.h"
#include "ItemMeta.generated.h"

class UItemDynamicSkill;
class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UItemMeta : public UPersistentDataContainer
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemMeta();

	/* Lore */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Lore")
	TArray<FString> Lore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Display Name")
	FString DisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Custom Model Data")
	int32 CustomModelData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Durability")
	int32 Durability; //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Rendering")
	bool bIsRenderItem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Rendering")
	UMaterialInstanceDynamic* DynamicRenderingInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Rendering")
	UTextureRenderTarget2D* TextureRenderTarget2D;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item Model Mesh")
	UStaticMesh* ItemModelMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item Entity Actor Class")
	TSubclassOf<AItemEntityActor> ItemEntityActorClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item Entity Actor")
	TObjectPtr<AItemEntityActor> ItemEntityActor;

	/*
	 *	Item Has its own Default Dynamic Skill. Information store in ItemClass
	 *	When Create ItemMeta, it read ItemClass to init ItemDynamicSkill. ItemDynamicSkill
	 *	Contain Item Default Skills and player could select Skills they want and
	 *	add these skills to BindItemDynamicSkill.
	 *
	 *	Note: Deserialize need to export ItemDynamicSkill and BindItemDynamicSkill
	 *	and Serialize will only check ItemDefault Skills, newly added Skills will
	 *	not override by Default Skills
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Item Dynamic Skill")
	TObjectPtr<UItemDynamicSkill> ItemDynamicSkill;

	/*
	 *	ItemDynamicSkill Store the item skills in ItemMeta, BindItemDynamicSkill
	 *	distribute Skills based on their Skill type, each type could only bind one
	 *	skill, for example, Skill Type SHIFT_INTERACT could only trigger one ItemSkill
	 *	(which is bind) even Item have 4 skills whose type is SHIFT_INTERACT
	 *	
	 *	Note: Deserialize need to export ItemDynamicSkill and BindItemDynamicSkill
	 *	and Serialize will load the BindItemDynamicSkill and its binding
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Item Dynamic Skill")
	TMap<EItemDynamicSkillSlot, TObjectPtr<UDAction>> BindItemDynamicSkill;

	/*!
	 * Add Specific Action to BindItemDynamicSkill, usually the action
	 * came from ItemDynamicSkill, but for some special equipment, like
	 * assemble equipment, different material could have various Skills.
	 *
	 * The function will automatically assign Action to correspond Action
	 * Type.
	 * 
	 * @param Instigator Who select the skill and bind to slot
	 * @param TargetAction The Action Instigator choose to bind
	 * @return true if bind success, false if original action is
	 * the same with new Action.
	 */
	UFUNCTION(BlueprintCallable, Category= "Item Dynamic Skill")
	bool AddActionToBindItemSkill(APawn* Instigator, UDAction* TargetAction);

	UFUNCTION(Blueprintable)
	virtual AItemEntityActor* CreateItemEntityActor(const UObject* WorldContextObject);
	UFUNCTION(Blueprintable)
	virtual void InitializeItemMetaData(UItem* ItemClass);

protected:
	// Called when the game starts 
	virtual void PostInitProperties() override;

public:
	// Native C++ Serialization
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject) override;
};
