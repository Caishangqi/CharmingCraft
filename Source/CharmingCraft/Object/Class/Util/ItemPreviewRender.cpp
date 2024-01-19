// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemPreviewRender.h"
#include "CharmingCraft/Core/Entity/Item/ItemTargetRenderActor.h"
#include "CharmingCraft/Core/Entity/Item/model/SwordActor.h"
#include "CharmingCraft/Interface/Meta/ItemMeta.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
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

/*!
 * @param InputMeta Input meta that prepare for manipulation 3d item meta specific
 * @param RenderWorld You need Specify world for spawn actor
 * @return UMaterialInstanceDynamic
 * 
 * Take Item Meta, use the item meta specified mesh and put the mesh into render target
 * then get the 2D MID from the render target actor
 */
UMaterialInstanceDynamic* UItemPreviewRender::RenderItem(UItemMeta* InputMeta, UWorld* RenderWorld)
{
	FVector SpawnLocation(-2000.f, -2000.f, -2000.f); // 设置生成位置为 (0,0,-2000)
	FRotator SpawnRotation(0.f, 0.f, 0.f); // 设置生成旋转为 (0,0,0)
	FTransform SpawnTransform(SpawnRotation, SpawnLocation); // 使用位置和旋转创建FTransform

	AItemTargetRenderActor* RenderActor = Cast<AItemTargetRenderActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(RenderWorld,
		                                                   AItemTargetRenderActor::StaticClass(), SpawnTransform));

	RenderActor->DropIconMesh->SetStaticMesh(InputMeta->ItemModelMesh);
	if (RenderActor)
	{
		UGameplayStatics::FinishSpawningActor(RenderActor, SpawnTransform);
		UMaterialInstanceDynamic* RenderMaterial = DuplicateObject<UMaterialInstanceDynamic>(
			RenderActor->OutPutMaterialInstanceDynamic, this);
		//RenderActor->SceneCaptureComponent->CaptureScene();
		RenderActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("(!) Successfully destroy RenderItem"))
		return RenderMaterial;
	}
	return nullptr;
}

/*!
 * @param InputMeta Input meta that prepare for manipulation weapon meta specific
 * @param RenderWorld You need Specify world for spawn actor
 * @return UMaterialInstanceDynamic
 * 
 * Take Weapon Meta, use the weapon meta specified weapon actor class to create actor and
 * attach to render actor component for render
 */
UMaterialInstanceDynamic* UItemPreviewRender::RenderItem(UWeaponMeta* InputMeta, UWorld* RenderWorld)
{
	FVector SpawnLocation(-20000.f, -20000.f, -2000.f); // 设置生成位置为 (0.f, 0.f, -2000.f)
	// -4300.f, 2000.f, 450.f
	FRotator SpawnRotation(0.f, 0.f, 0.f); // 设置生成旋转为 (0,0,0)
	FTransform SpawnTransform(SpawnRotation, SpawnLocation); // 使用位置和旋转创建FTransform
	FTransform DefaultTransform;
	/* Fist Spawn Render Actor Prepare for Render 3D Object */
	AItemTargetRenderActor* RenderActor = Cast<AItemTargetRenderActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(RenderWorld,
		                                                   AItemTargetRenderActor::StaticClass(), SpawnTransform));
	/* Prepare Spawn Weapon Actor form Meta, spawn from static class */
	AActor* WeaponActor = Cast<AActor>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(RenderWorld,
		                                                   InputMeta->WeaponActor, DefaultTransform));

	// Modify the Actor's properties here
	InputMeta->AssembleComponent(WeaponActor);
	// Modify the Actor's Position that fit the camera
	WeaponActor->SetActorRelativeLocation(FVector(-60.0f, -30.0f, -15.0f));
	WeaponActor->SetActorRelativeRotation(FRotator3d(0.0f, 350.0f, 0.0f));
	// Finish spawning the Actor
	UGameplayStatics::FinishSpawningActor(WeaponActor, SpawnTransform); // KeepWorldTransform
	WeaponActor->AttachToComponent(RenderActor->Root, FAttachmentTransformRules::KeepWorldTransform);
	// Tip: 在附加时保持组件的世界变换不变。不应该使用 FAttachmentTransformRules::KeepRelativeTransform

	if (RenderActor && WeaponActor)
	{
		UGameplayStatics::FinishSpawningActor(RenderActor, SpawnTransform);
		/* Prepare Render material copy it to variable*/
		UMaterialInstanceDynamic* RenderMaterial = DuplicateObject<UMaterialInstanceDynamic>(
			RenderActor->OutPutMaterialInstanceDynamic, this);
		RenderActor->SceneCaptureComponent->CaptureScene();
		RenderActor->Destroy();
		WeaponActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("(!) Successfully destroy RenderItem Actor"))
		return RenderMaterial;
	}
	return nullptr;
}

void UItemPreviewRender::UpdateMeshMaterialSlot(UStaticMesh* TargetMesh, int32 TargetMaterialIndex,
                                                UMaterial* InputMaterial)
{
	TargetMesh->SetMaterial(TargetMaterialIndex, InputMaterial);
}
