// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Data/PersistentDataContainer.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Item Skill")
	TObjectPtr<UItemDynamicSkill> ItemDynamicSkill;


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
