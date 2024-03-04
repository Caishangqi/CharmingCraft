// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockMeta.h"

#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/Block/BlockEntityActor.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
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
