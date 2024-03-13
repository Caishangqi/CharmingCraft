// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "CharmingCraft/Core/Log/Logging.h"

UItem::UItem()
{
	MaxStackSize = 64;
	// 
	FVector Position(100.0, 85.0, 70.0);
	// 旋转，这里使用欧拉角创建四元数旋转，假设只绕Z轴旋转90度
	FQuat Rotation(FRotator(0, -120.0, 0));
	// 缩放
	FVector Scale(1, 1, 1);
	FTransform SceneCaptureRenderTransform(Rotation, Position, Scale);
	RenderSpecifyTransform = SceneCaptureRenderTransform;
	OrthoWidth = 164;

	
	ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterial(TEXT("/Script/Engine.Material'/Game/CharmingCraft/Assets/textures/item/generic_item_material.generic_item_material'"));
	BaseMaterialAsset =  BaseMaterial.Object;
	
}

void UItem::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
}

void UItem::EndItemInteract()
{
}

void UItem::LoadLocalAsset()
{
	if (!AssetName.IsEmpty())
	{
		FString Path = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/CharmingCraft/Assets/textures/item/%s.%s'"), *AssetName, *AssetName);
		 ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(*Path);
		
		 ConstructorHelpers::FObjectFinder<UStaticMesh> MeshTexture(
			TEXT("/Script/Engine.StaticMesh'/Game/CharmingCraft/Assets/models/item/generic_item_mesh.generic_item_mesh'"));
		
		UE_LOG(LogChamingCraftCraftAsset, Warning, TEXT("2D Path: %s"),*Path);
		if (MeshTexture.Succeeded() && IconTexture.Succeeded())
		{
			Icon = IconTexture.Object;
			// We use the same static mesh on UItem constructor, so when we change the Material, all UItem static mesh
			// will change material. hence we should duplicate this mesh and apply to drop item.
			StaticMesh = DuplicateObject(MeshTexture.Object,GetOuter());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load Icon texture!"));
		}
	}
}

void UItem::CreateDynamicAsset()
{
	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterialAsset, GetOuter());
	DynamicMaterialInstance->SetTextureParameterValue(FName("Icon"), Icon);
	StaticMesh->SetMaterial(0,DynamicMaterialInstance);
}



