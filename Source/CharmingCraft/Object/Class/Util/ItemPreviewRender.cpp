// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPreviewRender.h"

#include "CharmingCraft/Entity/Item/ItemTargetRenderActor.h"
#include "CharmingCraft/Interface/Meta/ItemMeta.h"
#include "Kismet/GameplayStatics.h"

UItemPreviewRender* UItemPreviewRender::Instance = nullptr;

UItemPreviewRender* UItemPreviewRender::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UItemPreviewRender>();
		Instance->AddToRoot(); // 防止垃圾回收
	}
	return Instance;
}

UMaterialInstanceDynamic* UItemPreviewRender::RenderItem(UItemMeta* InputMeta, UWorld* RenderWorld)
{
	FVector SpawnLocation(0.f, 0.f, -2000.f); // 设置生成位置为 (0,0,-2000)
	FRotator SpawnRotation(0.f, 0.f, 0.f); // 设置生成旋转为 (0,0,0)
	FTransform SpawnTransform(SpawnRotation, SpawnLocation); // 使用位置和旋转创建FTransform

	AItemTargetRenderActor* RenderActor = Cast<AItemTargetRenderActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(RenderWorld,
		                                                   AItemTargetRenderActor::StaticClass(), SpawnTransform));
	RenderActor->DropModelMesh->SetStaticMesh(InputMeta->ItemModelMesh);
	if (RenderActor)
	{
		UGameplayStatics::FinishSpawningActor(RenderActor, SpawnTransform);
		UMaterialInstanceDynamic* RenderMaterial = DuplicateObject<UMaterialInstanceDynamic>(
			RenderActor->OutPutMaterialInstanceDynamic, this);
		RenderActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("(!) Successfully destroy RenderItem"))
		return RenderMaterial;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Faile to Spawn RenderItem"))
	}

	// TODO: 记得修复空指针
	return nullptr;
}
