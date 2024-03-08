// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockMeta.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Item/Block.h"
#include "Kismet/GameplayStatics.h"

UBlockMeta::UBlockMeta()
{
	bIsRenderItem = true;
	ItemEntityActorClass = nullptr;
}

AItemEntityActor* UBlockMeta::CreateItemEntityActor(const UObject* WorldContextObject)
{
	FTransform DefaultTransform;
	TObjectPtr<UItemStack> OuterItemStack = Cast<UItemStack>(this->GetOuter());


	TObjectPtr<ABlockEntityActor> BlockEntityActor = Cast<ABlockEntityActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(WorldContextObject,
		                                                   Cast<UBlock>(OuterItemStack->ItemClass.GetDefaultObject())->
		                                                   DefaultBlockEntityActorClass,
		                                                   DefaultTransform));
	UGameplayStatics::FinishSpawningActor(BlockEntityActor, DefaultTransform);
	return static_cast<AItemEntityActor*>(BlockEntityActor);
}

ABlockEntityActor* UBlockMeta::PrepareCreateBlockEntityActor(const UObject* WorldContextObject)
{
	FTransform DefaultTransform;
	TObjectPtr<UItemStack> OuterItemStack = Cast<UItemStack>(this->GetOuter());
	TObjectPtr<ABlockEntityActor> BlockEntityActor = Cast<ABlockEntityActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(WorldContextObject,
		                                                   Cast<UBlock>(OuterItemStack->ItemClass.GetDefaultObject())->
		                                                   DefaultBlockEntityActorClass,
		                                                   DefaultTransform));
	BlockEntityActor->DropTableData = DropTableData;
	return BlockEntityActor;
}

ABlockEntityActor* UBlockMeta::CreateBlockEntityActor(const UObject* WorldContextObject)
{
	FTransform DefaultTransform;
	TObjectPtr<ABlockEntityActor> BlockEntityActor = PrepareCreateBlockEntityActor(WorldContextObject);
	UGameplayStatics::FinishSpawningActor(BlockEntityActor, DefaultTransform);
	return BlockEntityActor;
}

void UBlockMeta::InitializeItemMetaData(UItem* ItemClass)
{
	Super::InitializeItemMetaData(ItemClass);
	DropTableData = Cast<UBlock>(ItemClass)->DropTableData;
	bDropSelf = Cast<UBlock>(ItemClass)->bDropSelf;
	// UE_LOG(LogChamingCraftCraftResource, Display,
	//        TEXT("[🗒️]  Load Drop Table to BlockMeta\n"
	// 	       "		 [D] Table Name =			%s\n"),
	//        *DropTableData->DropTableName.ToString());
}
