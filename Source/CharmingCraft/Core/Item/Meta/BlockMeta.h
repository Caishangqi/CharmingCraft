// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemMeta.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "BlockMeta.generated.h"

/**
 * 
 */
UCLASS()
class CHARMINGCRAFT_API UBlockMeta : public UItemMeta
{
	GENERATED_BODY()

public:
	UBlockMeta();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Drop Table")
	TObjectPtr<UDropTableData> DropTableData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Drop Table")
	bool bDropSelf = true;

	virtual AItemEntityActor* CreateItemEntityActor(const UObject* WorldContextObject) override;

	UFUNCTION(BlueprintCallable)
	ABlockEntityActor* PrepareCreateBlockEntityActor(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable)
	ABlockEntityActor* CreateBlockEntityActor(const UObject* WorldContextObject);

	virtual void InitializeItemMetaData(UItem* ItemClass) override;
};
