// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentRenderComponent.h"

#include "DCharacter.h"
#include "EquipmentManagerComponent.h"
#include "ItemStack.h"
#include "CharmingCraft/Interface/Meta/HelmetMeta.h"
#include "EquipPart/EquipPartHelmetCore.h"

// Sets default values for this component's properties
UEquipmentRenderComponent::UEquipmentRenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	UE_LOG(LogTemp, Warning, TEXT("UEquipmentRenderComponent Initialize"));
	UEquipmentManagerComponent* EquipmentManagerComponent = Cast<UEquipmentManagerComponent>(GetOuter());
	//EquipmentManagerComponent->HelmetSlot
}


// Called when the game starts
void UEquipmentRenderComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UEquipmentRenderComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentRenderComponent::UpdateRender()
{
	// UEquipmentManagerComponent* EquipmentManagerComponent = Cast<UEquipmentManagerComponent>(GetOuter());
	// if (EquipmentManagerComponent->IsOccupied(EquipmentManagerComponent->HelmetSlot))
	// {
	// 	const UHelmetMeta* HelmetMeta = Cast<UHelmetMeta>(EquipmentManagerComponent->HelmetSlot->ItemMeta);
	//
	// 	const FDArmorMaterial* ArmorMaterial = HelmetMeta->HelmetCore->ComponentMaterial.GetRow<FDArmorMaterial>(
	// 		FString("Cactus"));
	// 	HelmetMeta->HelmetCore->PartMesh = ArmorMaterial->CoreTexture;
	// 	//设置HelmetSlot 网格体材质
	// 	ADCharacter* PlayerCharacter = Cast<ADCharacter>(EquipmentManagerComponent->GetOwner());
	// 	UStaticMeshComponent* HelmetSlot = nullptr;
	// 	USkeletalMeshComponent* PlayerMesh = PlayerCharacter->FindComponentByClass<USkeletalMeshComponent>();
	// 	TArray<USceneComponent*> ChildComponents;
	// 	PlayerMesh->GetChildrenComponents(true, ChildComponents);
	// 	for (USceneComponent* Child : ChildComponents)
	// 	{
	// 		if (Child->GetName() == TEXT("Helmet Slot"))
	// 		{
	// 			HelmetSlot = Cast<UStaticMeshComponent>(Child);
	// 			break;
	// 		}
	// 	}
	//
	// 	if (HelmetSlot)
	// 	{
	// 		// 现在您有了Helmet Slot组件的引用，可以进行进一步的操作
	// 		HelmetSlot->SetMaterial(0, ArmorMaterial->CoreTexture);
	// 	}
	// }
}
