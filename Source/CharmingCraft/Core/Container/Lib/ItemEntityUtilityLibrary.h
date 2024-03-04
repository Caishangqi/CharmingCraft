// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Entity/Item/ItemTargetRenderActor.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ItemEntityUtilityLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "ItemEntityUtilityLibrary"))
class CHARMINGCRAFT_API UItemEntityUtilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*!
	 * Capture Target Actor ItemEntityActor and return UMaterialInstanceDynamic,
	 * user need provide ItemEntityActorClass In order to work properly
	 * @param TargetItemStack Target Actor you want to get 2D icon from 3D
	 * @param RenderWorld The world that perform actor spawn and screen capture
	 */
	UFUNCTION(BlueprintCallable, Category = "Render")
	static void SetItem2DIconFromItemEntity(UItemStack* TargetItemStack, UWorld* RenderWorld)
	{
		if (TargetItemStack != nullptr && TargetItemStack->ItemMeta->bIsRenderItem)
		{
			TObjectPtr<UItemMeta> ItemMeta = TargetItemStack->ItemMeta;
			ItemMeta->DynamicRenderingInstance = RenderItem(ItemMeta, RenderWorld);
		}
	};

	/*!
	 * @param InputMeta Input meta that prepare for manipulation 3d item meta specific
	 * @param RenderWorld You need Specify world for spawn actor
	 * @return UMaterialInstanceDynamic
	 * 
	 * Take Item Meta, use the item meta specified mesh and put the mesh into render target
	 * then get the 2D MID from the render target actor
	 */
	UFUNCTION(BlueprintCallable, Category = "Render")
	static UMaterialInstanceDynamic* RenderItem(UItemMeta* InputMeta, UWorld* RenderWorld)
	{
		FVector SpawnLocation(-20000.f, -20000.f, -2000.f); // 设置生成位置为 (0.f, 0.f, -2000.f)
		// -4300.f, 2000.f, 450.f
		FRotator SpawnRotation(0.f, 0.f, 0.f); // 设置生成旋转为 (0,0,0)
		FTransform SpawnTransform(SpawnRotation, SpawnLocation); // 使用位置和旋转创建FTransform
		/* Fist Spawn Render Actor Prepare for Render 3D Object */
		TObjectPtr<AItemTargetRenderActor> RenderActor = Cast<AItemTargetRenderActor>(
			UGameplayStatics::BeginDeferredActorSpawnFromClass(RenderWorld,
			                                                   AItemTargetRenderActor::StaticClass(), SpawnTransform));
		// ItemEntityActor
		TObjectPtr<AItemEntityActor> ItemEntityActor = InputMeta->CreateItemEntityActor(RenderWorld);

		/* Prepare Spawn Weapon Actor form Meta, spawn from static class */
		// Modify the Actor's properties here
		// Modify the Actor's Position that fit the camera
		ItemEntityActor->SetActorRelativeLocation(FVector(-60.0f, -30.0f, -15.0f));
		ItemEntityActor->SetActorRelativeRotation(FRotator3d(0.0f, 350.0f, 0.0f));
		ItemEntityActor->SetActorTransform(SpawnTransform);
		// Finish spawning the Actor
		//UGameplayStatics::FinishSpawningActor(WeaponActor, SpawnTransform); // KeepWorldTransform
		ItemEntityActor->AttachToComponent(RenderActor->Root, FAttachmentTransformRules::KeepWorldTransform);
		// Tip: 在附加时保持组件的世界变换不变。不应该使用 FAttachmentTransformRules::KeepRelativeTransform
		if (RenderActor && ItemEntityActor)
		{
			UGameplayStatics::FinishSpawningActor(RenderActor, SpawnTransform);
			/* Prepare Render material copy it to variable*/
			UMaterialInstanceDynamic* RenderMaterial = DuplicateObject<UMaterialInstanceDynamic>(
				RenderActor->OutPutMaterialInstanceDynamic, InputMeta);
			// Read Render Data from ItemClass
			TObjectPtr<UItemStack> OuterItemStack = Cast<UItemStack>(InputMeta->GetOuter());

			FTransform RenderSpecifyTransform = OuterItemStack->ItemClass.GetDefaultObject()->RenderSpecifyTransform;

			RenderActor->SceneCaptureComponent->SetRelativeRotation(RenderSpecifyTransform.GetRotation());
			RenderActor->SceneCaptureComponent->SetRelativeLocation(RenderSpecifyTransform.GetLocation()); // 100 85 70
			RenderActor->SceneCaptureComponent->OrthoWidth = OuterItemStack->ItemClass.GetDefaultObject()->OrthoWidth;

			RenderActor->SceneCaptureComponent->CaptureScene();
			RenderActor->Destroy();
			ItemEntityActor->Destroy();
			//UE_LOG(LogTemp, Warning, TEXT("(!) Successfully destroy RenderItem Actor"))
			return RenderMaterial;
		}
		return nullptr;
	};
	UFUNCTION(BlueprintCallable, Category = "Material")
	static void UpdateMeshMaterialSlot(UStaticMesh* TargetMesh, int32 TargetMaterialIndex,
	                                   UMaterial* InputMaterial)
	{
		TargetMesh->SetMaterial(TargetMaterialIndex, InputMaterial);
	}
};
