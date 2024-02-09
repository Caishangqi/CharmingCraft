// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/Save/Interface/ISerializable.h"
#include "CharmingCraft/Core/Save/Data/PersistentDataContainer.h"
#include "ItemMeta.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UItemMeta : public UPersistentDataContainer, public ISerializable
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

	virtual void UpdateRender(UWorld* RenderWorld);

protected:
	// Called when the game starts 
	virtual void PostInitProperties() override;

public:
	// Native C++ Serialization
	virtual TSharedPtr<FJsonObject> SerializeToJson() override;
	virtual UObject* DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject) override;
	// Unreal BluePrint Serialization Interface Implementation
	virtual FString Serialize_Implementation() override;
	virtual UObject* Deserialize_Implementation(const FString& SerializeData) override;
};
