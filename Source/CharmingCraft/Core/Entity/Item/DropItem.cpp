// Fill out your copyright notice in the Description page of Project Settings.

#include "DropItem.h"
#include "DCharacter.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ADropItem::ADropItem()
{
	// Create the invisible collision box and attach it to the RootComponent of the actor
	InvisibleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InvisibleCollision"));
	RootComponent = InvisibleCollision;
	// Set the size of the collision box
	InvisibleCollision->SetBoxExtent(FVector(50.f, 50.f, 100.f)); // You can adjust the size as needed

	// Ensure it doesn't render anything
	InvisibleCollision->SetVisibility(true);

	// Enable collision
	InvisibleCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	DropIconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropIconMesh"));
	DropIconMesh->SetupAttachment(RootComponent); // 附加到Root组件
	// Set up transform
	FRotator DropIconRotation = FRotator(0.0f, 90.0f, -30.0f); // Pitch, Yaw, Roll
	FVector DropIconLocation = FVector(0.0f, -50.0f, 8.0f); // X, Y, Z
	DropIconMesh->SetRelativeLocation(DropIconLocation);
	DropIconMesh->SetRelativeRotation(DropIconRotation);
	DropIconMesh->SetCastShadow(false);
	DropIconMesh->SetReceivesDecals(false);
	SetupCollision();
}

void ADropItem::SetupCollision()
{
	// 设置Pawn通道的碰撞响应为ECR_Ignore
	DropIconMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void ADropItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// bRenderingResourcesInitialized
void ADropItem::Initialize(UItemStack* PassItemStack)
{
	ItemStack = PassItemStack;
	if (ItemStack->ItemMeta->IsA(UWeaponMeta::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemStack->ItemMeta->IsA(UWeaponMeta::StaticClass())"));
		FVector WeaponLocation(0.0f, -50.0f, 5.0f);
		FRotator WeaponRotation = FRotator(0.0f, 90.0f, -30.0f);
		FTransform DefaultTransform(WeaponRotation, WeaponLocation);
		ItemStack->ItemMeta->ItemEntityActor = ItemStack->ItemMeta->CreateItemEntityActor(this);
		AItemEntityActor* WeaponActor = Cast<AItemEntityActor>(ItemStack->ItemMeta->ItemEntityActor);
		WeaponActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else if (ItemStack->ItemMeta->bIsRenderItem)
	{
		if (IsValid(ItemStack->ItemMeta->ItemModelMesh))
		{
			UE_LOG(LogTemp, Warning, TEXT("ADropItem::Initialize Mesh Ready"));
		}
		FRotator DropIconRotation = FRotator(0.0f, -90.0f, 0.0f); // Pitch, Yaw, Roll
		DropIconMesh->SetRelativeRotation(DropIconRotation);
		DropIconMesh->SetStaticMesh(ItemStack->ItemMeta->ItemModelMesh);
	}
	else
	{
		DropIconMesh->SetStaticMesh(ItemStack->GetItemClass()->StaticMesh);
	}
}


void ADropItem::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("ADropItem::Interact_Implementation"));

	//Super::Interact_Implementation(InstigatorPawn);
	ADCharacter* Player = Cast<ADCharacter>(InstigatorPawn);

	UE_LOG(LogTemp, Warning, TEXT("ADropItem::Interact_Implementation -> %s, %d"),
	       *this->ItemStack->GetItemClass()->DisplayName.ToString(), this->ItemStack->Amount);
	int32 RemainQuantity = Player->InventoryComponent->AddToInventory(this->ItemStack).RemainQuantity;
	if (RemainQuantity == 0)
	{
		TArray<AActor*> AttachedActors;
		this->GetAttachedActors(AttachedActors);
		// Delete Attach Actor for Weapon Actors
		if (AttachedActors.Num() != 0)
		{
			for (const auto AttachedActor : AttachedActors)
			{
				AttachedActor->Destroy();
			}
		}

		Destroy();
	}
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ADropItem::BeginPlay()"));
}
