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

	virtual AItemEntityActor* CreateItemEntityActor(const UObject* WorldContextObject, AActor* Owner) override;

	/*!
	 * Prepare to create BlockEntityActor, modify and inject different block data
	 * or itemmeta etc.
	 * @param WorldContextObject 
	 * @param Owner The Block that related to level or other Actor
	 * @return ABlockEntityActor
	 */
	UFUNCTION(BlueprintCallable)
	ABlockEntityActor* PrepareCreateBlockEntityActor(const UObject* WorldContextObject, AActor * Owner);
	UFUNCTION(BlueprintCallable)
	ABlockEntityActor* CreateBlockEntityActor(const UObject* WorldContextObject, AActor* Owner);

	virtual void InitializeItemMetaData(UItem* ItemClass) override;
};
