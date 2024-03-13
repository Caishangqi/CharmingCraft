// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceEntityActor.h"

#include "ResourceEntityGeometryActor.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Container/Lib/ItemEntityUtilityLibrary.h"
#include "CharmingCraft/Core/Resource/Lib/ResourceGenerateLibrary.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Components/BoxComponent.h"

// Sets default values
AResourceEntityActor::AResourceEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	RootComponent = DefaultSceneRoot;
	HitBox->SetupAttachment(RootComponent);
	bIsAllowToDamage = true;
	// Data
	CurrentStage = 0;
}

// Called when the game starts or when spawned
void AResourceEntityActor::BeginPlay()
{
	Super::BeginPlay();
	GameEventHandler = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance())->GamePlayLogicManager;
}

// Called every frame
void AResourceEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResourceEntityActor::ResetHealth()
{
	UE_LOG(LogChamingCraftCraftResource, Display,
	       TEXT("[⛏️]  Resource %s has restore health"), *this->GetName());
	ResourceData.CurrentHeath = ResourceData.MaxHeath;
}

int32 AResourceEntityActor::ReduceResourceHeath(int32 Delta)
{
	this->ResourceData.CurrentHeath = this->ResourceData.CurrentHeath - Delta;
	return this->ResourceData.CurrentHeath;
}

bool AResourceEntityActor::OnBlockBreak_Implementation(AActor* InstigatorContext, AActor* BlockBreak)
{
	GameEventHandler->OnResourceEntityBreakEvent(InstigatorContext, this);
	
	Execute_OnBlockDrop(this, InstigatorContext, DropTableData.GetDefaultObject());
	
	// Animation
	if (ResourceGeometryData.OnBreakGeometry)
	{
		AActor* DestructibleActor = GetWorld()->SpawnActor<
			AActor>(ResourceGeometryData.OnBreakGeometry, GetActorLocation(), GetActorRotation());
	}

	// Destroy Actor
	this->Destroy();
	
	return IBreakableInterface::OnBlockBreak_Implementation(InstigatorContext, BlockBreak);
}

bool AResourceEntityActor::OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableDataContext)
{
	if (bDropSelf)
	{
		
	}
	else
	{
		const FTransform SpawnTransform(
			this->GetActorLocation() + this->GetActorUpVector() * 50);
		FVector LaunchDirection = this->GetActorUpVector() * 100 + FVector(0, 0, 50);
		FVector LaunchVelocity = LaunchDirection * 2;
		
		TArray<UItemStack *> ItemStackList = UResourceGenerateLibrary::GenerateDropItemFromDropData(this->GetWorld(),DropTableDataContext);
		if (ItemStackList.Num() ==0) return false;
		
			for (auto ItemStack : ItemStackList)
			{
				if (ItemStack!= nullptr)
				{
					GameEventHandler->OnItemDropEvent(ItemStack, this);
					UItemEntityUtilityLibrary::DropItemInWorld(this->GetWorld(), ItemStack, SpawnTransform, LaunchVelocity);
				}
				
			}
		
		
	}
	return IBreakableInterface::OnBlockDrop_Implementation(Block, DropTableDataContext);
}



void AResourceEntityActor::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	UE_LOG(LogChamingCraftCraftResource, Display,
	       TEXT("[⛏️]  Event trigger at AResourceEntityActor::OnActionHit_Implementation()"));
	UE_LOG(LogChamingCraftCraftResource, Display,
	       TEXT(
		       "		 [I] Instigator =		%s\n"
		       "		 [T] Target Resource Actor =		%s\n"
		       "		 [-] Target Resource Heath =		%d/%d\n"
		       "		 [+] Delta Damage =		%f"
	       ),
	       *InstigatorPawn->GetName(), *this->GetName(),
	       this->ResourceData.CurrentHeath, this->ResourceData.MaxHeath, HitData.Damage
	);

	if (ResourceData.ResetHeath)
	{
		// 设置一个倒计时定时器
		GetWorld()->GetTimerManager().SetTimer(ResourceInternalTimer, this, &AResourceEntityActor::ResetHealth,
		                                       ResourceData.ResetHealthTime, false);
		if (ReduceResourceHeath(HitData.Damage) <= 0)
		{
			Execute_OnBlockBreak(this, InstigatorPawn, this);
		}
	}

	if (ResourceGeometryData.OnDamageGeometry)
	{
		UE_LOG(LogChamingCraftCraftResource, Display,
		   TEXT("[⛏️]  Spawn OnDamage Entity Geometry Actor"));
		AActor* DestructibleActor = GetWorld()->SpawnActor<
			AActor>(ResourceGeometryData.OnDamageGeometry, GetActorLocation(), GetActorRotation());
	}
}
