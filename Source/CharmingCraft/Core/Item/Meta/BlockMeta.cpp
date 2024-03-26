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

	TObjectPtr<AItemEntityActor> AttachedActor = Cast<AItemEntityActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(WorldContextObject, AItemEntityActor::StaticClass(), DefaultTransform));

	if (AttachedActor)
	{
		// 设置ChildActorComponent的ChildActorClass
		if (OuterItemStack && OuterItemStack->ItemClass)
		{
			// 获取默认的BlockEntityActor类
			TSubclassOf<ABlockEntityActor> DefaultBlockEntityActorClass = Cast<UBlock>(OuterItemStack->ItemClass.GetDefaultObject())->DefaultBlockEntityActorClass;
			// 确保ChildActorComponent存在并设置其ChildActorClass
			if (AttachedActor->ChildActorComponent && DefaultBlockEntityActorClass)
			{
				AttachedActor->ChildActorComponent->SetChildActorClass(DefaultBlockEntityActorClass);
			}
		}

		UGameplayStatics::FinishSpawningActor(AttachedActor, DefaultTransform);
		
		// 现在ChildActorComponent会创建BlockEntityActor实例
		AttachedActor->ChildActorComponent->CreateChildActor();
		
		if (AActor* ChildActor = AttachedActor->ChildActorComponent->GetChildActor())
		{
			// 确保BlockEntityActor正确地附加到AttachedActor
			ChildActor->AttachToActor(AttachedActor, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		return AttachedActor;
	}

	return nullptr;
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
	BlockEntityActor->Material = OuterItemStack->Material;
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
}
