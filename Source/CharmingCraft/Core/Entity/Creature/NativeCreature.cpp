// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeCreature.h"

#include "CharmingCraft/Core/Buff/BuffHandlerComponent.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Container/Lib/ItemEntityUtilityLibrary.h"
#include "CharmingCraft/Core/Resource/Lib/ResourceGenerateLibrary.h"
#include "CharmingCraft/Core/Resource/Loot/NativeLootEntity.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/UI/HealthIndicator.h"
#include "CharmingCraft/Object/Components/UI/DamageIndicator.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANativeCreature::ANativeCreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CreatureAttributeComponent = CreateDefaultSubobject<UDAttributeComponent>("Creature Attribute Component");
	DamageIndicator = CreateDefaultSubobject<UDamageIndicator>("DamageIndicator");
	DamageIndicator->SetupAttachment(GetRootComponent());
	HealthIndicator = CreateDefaultSubobject<UHealthIndicator>("HealthIndicator");
	HealthIndicator->SetupAttachment(GetRootComponent());
	BuffHandlerComponent = CreateDefaultSubobject<UBuffHandlerComponent>("BuffHandlerComp");
	ActionComponent = CreateDefaultSubobject<UDActionComponent>("ActionComp");
	
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	HitBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ANativeCreature::BeginPlay()
{
	Super::BeginPlay();
	/* Fix 2014/1/13 Bind Delegate multiply time when re stream the level */
	if (!CreatureAttributeComponent->OnHealthChanged.IsBound())
	{
		CreatureAttributeComponent->OnHealthChanged.AddDynamic(this, &ANativeCreature::HandleHealthChanged);
	}
}


// Called every frame
void ANativeCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANativeCreature::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags;
	FGameplayTagContainer ComponentTags;
	ActionComponent->GetOwnedGameplayTags(ComponentTags);
	TagContainer.AppendTags(ComponentTags);
}


// Called to bind functionality to input
void ANativeCreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANativeCreature::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	if (!CreatureAttributeComponent->IsDead)
	{
		CreatureAttributeComponent->SubmitHitData(HitData);
		HitReaction(HitData.DamageResponse);
	}
}

void ANativeCreature::HandleDamageIndicator_Implementation(FHitData HitData)
{
	IUIProcess::HandleDamageIndicator_Implementation(HitData);
}

void ANativeCreature::HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
                                                         float Health, float HealthDelta)
{
	IDamageable::HandleHealthChanged_Implementation(InstigatorPawn, OwningComp, Health, HealthDelta);
}


void ANativeCreature::HandleDeath_Implementation(APawn* InstigatorPawn)
{
	GetGameEventHandler_Implementation()->OnOnCreatureDeadEvent(InstigatorPawn, this);
	LootFromObject_Implementation(this);
	IDamageable::HandleDeath_Implementation(InstigatorPawn);
}

bool ANativeCreature::IsDead_Implementation()
{
	return CreatureAttributeComponent->IsDead;
}

void ANativeCreature::LootFromObject_Implementation(UObject* InstigatorObject)
{
	if (DropLoot && DropTableData != nullptr)
	{
		TArray<UItemStack*> LootItemStackList = UResourceGenerateLibrary::GenerateDropItemFromDropData(
			this->GetWorld(), DropTableData.GetDefaultObject());
		if (LootItemStackList.Num() > 0)
		{
			if (PackLoot)
			{
				// Generate Loot Entity
				FTransform SpawnTransform(GetActorRotation(), GetActorLocation());
				TObjectPtr<ANativeLootEntity> LootEntity = Cast<ANativeLootEntity>(
					UGameplayStatics::BeginDeferredActorSpawnFromClass(
						this, LootEntityClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::Undefined, this));
				LootEntity->GenerateLootContent(LootItemStackList);
				UGameplayStatics::FinishSpawningActor(LootEntity, SpawnTransform);
			}
			else
			{
				const FTransform SpawnTransform(
					this->GetActorLocation() + this->GetActorUpVector() * 50);
				FVector LaunchDirection = this->GetActorUpVector() * 100 + FVector(0, 0, 50);
				FVector LaunchVelocity = LaunchDirection * 2;
				for (auto ItemStack : LootItemStackList)
				{
					if (ItemStack != nullptr)
					{
						GetGameEventHandler_Implementation()->OnItemDropEvent(ItemStack, this);
						UItemEntityUtilityLibrary::DropItemInWorld(this->GetWorld(), ItemStack, SpawnTransform,
						                                           LaunchVelocity);
					}
				}
			}
		}
	}
}

void ANativeCreature::Interact_Implementation(APawn* InstigatorPawn)
{
	IMouseInteractInterface::Interact_Implementation(InstigatorPawn);
}

UCharmingCraftInstance* ANativeCreature::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UGameEventHandler* ANativeCreature::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}

UWorldManager* ANativeCreature::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}


void ANativeCreature::HitReaction_Implementation(EDamageResponse Response)
{
}
