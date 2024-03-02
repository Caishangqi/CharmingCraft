#pragma once
#include "CoreMinimal.h"
#include "FItemMeta.generated.h"
// #include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
class AItemEntityActor;

USTRUCT(BlueprintType)
struct FItemMetaData
{
	GENERATED_BODY()

public:
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Item Entity Actor Class")
	TSubclassOf<AItemEntityActor> ItemEntityActorClass;
};
