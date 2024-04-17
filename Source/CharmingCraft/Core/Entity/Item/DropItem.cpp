// Fill out your copyright notice in the Description page of Project Settings.

#include "DropItem.h"
#include "DCharacter.h"
#include "CharmingCraft/Interface/Meta/WeaponMeta.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "CharmingCraft/Core/Item/Meta/BlockMeta.h"
#include "CharmingCraft/Core/Item/RenderActor/ItemEntityActor.h"
#include "CharmingCraft/Core/Item/RenderActor/Abstract/EquipmentEntityActor.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Components/BoxComponent.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;
	// Create the invisible collision box and attach it to the RootComponent of the actor
	InvisibleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InvisibleCollision"));
	InvisibleCollision->SetSimulatePhysics(true);
	InvisibleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InvisibleCollision->BodyInstance.bLockXRotation = true;
	InvisibleCollision->BodyInstance.bLockYRotation = true;
	InvisibleCollision->BodyInstance.bLockZRotation = true;

	//
	FCollisionResponseContainer CollisionResponse;
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);

	// 其他通道保持默认值或设置为忽略（ECR_Ignore）
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	InvisibleCollision->SetCollisionResponseToChannels(CollisionResponse);
	InvisibleCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	InvisibleCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InvisibleCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

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
	FRotator DropIconRotation = FRotator(0.0f, 135.0f, -30.0f); // Pitch, Yaw, Roll
	FVector DropIconLocation = FVector(0.0f, 0.0f, 0.0f); // X, Y, Z
	DropIconMesh->SetRelativeLocation(DropIconLocation);
	DropIconMesh->SetRelativeRotation(DropIconRotation);
	DropIconMesh->SetCastShadow(false);
	DropIconMesh->SetReceivesDecals(false);
	
	DropIconMesh->SetCanEverAffectNavigation(false);
	InvisibleCollision->SetCanEverAffectNavigation(false);
}


// bRenderingResourcesInitialized
void ADropItem::Initialize(UItemStack* PassItemStack, AActor * DropItemOwner)
{
	ItemStack = PassItemStack;
	
	if (ItemStack->ItemMeta->IsA(UIntegratedMeta::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemStack->ItemMeta->IsA(UWeaponMeta::StaticClass())"));
		FVector WeaponLocation(0.0f, -50.0f, 5.0f);
		FRotator WeaponRotation = FRotator(0.0f, 90.0f, -30.0f);
		FTransform DefaultTransform(WeaponRotation, WeaponLocation);
		if (ItemStack->ItemMeta->ItemEntityActorClass)
		{
			ItemStack->ItemMeta->ItemEntityActor = ItemStack->ItemMeta->CreateItemEntityActor(this, Owner);
			AItemEntityActor* ItemEntityActor = Cast<AItemEntityActor>(ItemStack->ItemMeta->ItemEntityActor);
			ItemEntityActor->AttachToComponent(DropIconMesh, FAttachmentTransformRules::KeepRelativeTransform);
			//ItemEntityActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
	else if (ItemStack->ItemMeta->IsA(UBlockMeta::StaticClass())) // Handle Block Item Drop
	{
		AItemEntityActor* ItemEntityActor = Cast<UBlockMeta>(ItemStack->ItemMeta)->CreateItemEntityActor(this, Owner);
		FVector Scale(0.75, 0.75, 0.75);
		ItemEntityActor->AttachToComponent(DropIconMesh, FAttachmentTransformRules::KeepRelativeTransform);
		ItemEntityActor->SetActorTransform(FTransform(GetActorRotation(), GetActorLocation(), Scale));
	}
	else
	{
		ItemStack->ItemClass->GetDefaultObject<UItem>()->CreateDynamicAsset();
		DropIconMesh->SetStaticMesh(ItemStack->ItemClass->GetDefaultObject<UItem>()->StaticMesh);
		DropIconMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
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
	// 旋转
	TArray<TObjectPtr<AActor>> OutActors;
	GetAttachedActors(OutActors);
	for (auto OutActor : OutActors)
	{
		TObjectPtr<UStaticMeshComponent> StaticMeshComponent = Cast<UStaticMeshComponent>(
			OutActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

		TObjectPtr<UBoxComponent> BoxComponent = Cast<UBoxComponent>(OutActor->GetComponentByClass(UBoxComponent::StaticClass()));
		if (StaticMeshComponent)
		{
			StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		}
	}
}

void ADropItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// 计算新的旋转角度
	CurrentRotationAngle += RotationSpeed * DeltaSeconds * RotationDirection;

	// 如果旋转角度达到了最大值，改变旋转方向
	if (FMath::Abs(CurrentRotationAngle) >= MaxRotationAngle)
	{
		RotationDirection *= -1;
		// 保证旋转角度不超过最大值
		CurrentRotationAngle = FMath::Sign(CurrentRotationAngle) * MaxRotationAngle;
	}

	// 应用新的旋转
	FRotator NewRotation = DropIconMesh->GetRelativeRotation();
	NewRotation.Yaw += RotationSpeed * DeltaSeconds * RotationDirection; // 根据旋转方向更新Yaw值
	DropIconMesh->SetRelativeRotation(NewRotation);


	// 上下波动
	FVector NewLocation = DropIconMesh->GetRelativeLocation();
	BobbingPhase += DeltaSeconds * BobbingSpeed;
	NewLocation.Z += FMath::Sin(BobbingPhase) * BobbingAmplitude;
	DropIconMesh->SetRelativeLocation(NewLocation);
}
