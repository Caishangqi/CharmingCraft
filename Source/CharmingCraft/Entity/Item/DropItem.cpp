// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"

#include "DCharacter.h"
#include "CharmingCraft/Object/Components/DInventoryComponent.h"
#include "CharmingCraft/Object/Components/ItemStack.h"

ADropItem::ADropItem()
{
	ItemStack = CreateDefaultSubobject<UItemStack>("Default ItemStack");


	// 创建一个USceneComponent并将其设置为根组件
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	DropIconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropIconMesh"));
	DropIconMesh->SetupAttachment(RootComponent); // 附加到Root组件
	// 设置旋转
	FRotator DropIconRotation = FRotator(0.0f, 90.0f, -30.0f); // Pitch, Yaw, Roll
	FVector DropIconLocation = FVector(0.0f, 0.0f, 8.0f); // X, Y, Z
	DropIconMesh->SetRelativeLocation(DropIconLocation);
	DropIconMesh->SetRelativeRotation(DropIconRotation);

	DropModelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropModelMesh"));
	DropModelMesh->SetupAttachment(RootComponent); //
	SetupCollision();
}

void ADropItem::SetupCollision()
{
	// 设置Pawn通道的碰撞响应为ECR_Ignore
	DropIconMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void ADropItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADropItem::Initialize(UItemStack* PassItemStack)
{
	this->ItemStack = PassItemStack;
	//
	this->DropIconMesh->SetStaticMesh(this->ItemStack->GetItemClass()->StaticMesh);
}

void ADropItem::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("ADropItem::Interact_Implementation"));

	Super::Interact_Implementation(InstigatorPawn);
	ADCharacter* Player = Cast<ADCharacter>(InstigatorPawn);

	UE_LOG(LogTemp, Warning, TEXT("ADropItem::Interact_Implementation -> %s, %d"),
	       *this->ItemStack->GetItemClass()->DisplayName.ToString(), this->ItemStack->Amount);
	int32 RemainQuantity = Player->InventoryComponent->AddToInventory(this->ItemStack).RemainQuantity;
	if (RemainQuantity == 0)
	{
		Destroy();
	}
}
