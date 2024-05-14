// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockEntityActor.h"

#include "CharmingCraft/Core/Builds/Data/FPlaceValidation.h"
#include "CharmingCraft/Core/Bus/GameEventHandler.h"
#include "CharmingCraft/Core/Container/Lib/ItemEntityUtilityLibrary.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "../Core/CharmingCraftInstance.h"
#include "Components/BoxComponent.h"


// Sets default values
ABlockEntityActor::ABlockEntityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SceneComponent->SetRelativeLocation(FVector(50, 50, 0)); // Caution: DO NOT TOUCH, set to center in 100x100 XY grid
	RootComponent = SceneComponent;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->InitBoxExtent(FVector(48.0f, 48.0f, 48.0f));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetupAttachment(RootComponent);
	EnableBlockCollision();
	//
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABlockEntityActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABlockEntityActor::OnOverlapEnd);
	//
	Scale = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scale Component"));
	Scale->SetupAttachment(RootComponent);
	Scale->SetRelativeLocation(FVector(-5, -5, -5));
	Scale->SetRelativeScale3D(FVector(110, 100, 110));
	///Script/Engine.StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT(
		"/Script/Engine.StaticMesh'/Engine/Functions/Engine_MaterialFunctions02/SupportFiles/1x1x1_Box_Pivot_-XYZ.1x1x1_Box_Pivot_-XYZ'"));
	if (MeshAsset.Succeeded())
	{
		Scale->SetStaticMesh(MeshAsset.Object);
	}
	Scale->SetVisibility(false);
	Scale->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	Scale->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
}

// Called when the game starts or when spawned
void ABlockEntityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlockEntityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlockEntityActor::DisableBlockCollision()
{
	FCollisionResponseContainer CollisionResponse;
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);

	// 其他通道保持默认值或设置为忽略（ECR_Ignore）
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Overlap);
	CollisionBox->SetCollisionResponseToChannels(CollisionResponse);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	CollisionBox->SetCanEverAffectNavigation(false);
}

void ABlockEntityActor::EnableBlockCollision()
{
	FCollisionResponseContainer CollisionResponse;
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Block);

	// 其他通道保持默认值或设置为忽略（ECR_Ignore）
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionResponse.SetResponse(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannels(CollisionResponse);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionBox->SetCanEverAffectNavigation(true);
}

void ABlockEntityActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	// 处理开始重叠的逻辑
	if (OtherActor != this)
	{
		bIsCollied = true;
	}
	UE_LOG(LogChamingCraftBuild, Display,
	       TEXT("[📦]  Current Block is Overlap\n"
		       "		 [A] Actor Name =			%s\n"
		       "		 [B] Is Collied =			%hhd"
	       ), *this->GetName(),
	       bIsCollied);
}

void ABlockEntityActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsCollied = false;
}

void ABlockEntityActor::ChangeValidationCollidedType(EBuildCollidedType NewType,
                                                     const FPlaceValidation& PlaceValidation)
{
	switch (NewType)
	{
	case EBuildCollidedType::VALID:
		Scale->SetMaterial(0, PlaceValidation.ValidMaterial);
		break;
	case EBuildCollidedType::COLLIDED:
		Scale->SetMaterial(0, PlaceValidation.ColliedMaterial);
		break;
	case EBuildCollidedType::WARNING:
		Scale->SetMaterial(0, PlaceValidation.WarningMaterial);
		break;
	}
}

void ABlockEntityActor::EnablePreviewScaleBox()
{
	Scale->SetVisibility(true);
	IVisualEnhancementInterface::Execute_SetObjectTranslucent(this, 0.0f);
}

void ABlockEntityActor::DisablePreviewScaleBox()
{
	Scale->SetVisibility(false);
	IVisualEnhancementInterface::Execute_SetObjectTranslucent(this, 1.0f);
}

bool ABlockEntityActor::OnBlockBreak_Implementation(AActor* InstigatorCharacter, AActor* BlockBreak)
{
	GetGameEventHandler()->
	                                                 OnBlockBreakEvent(this, InstigatorCharacter);
	Execute_OnBlockDrop(this, InstigatorCharacter, DropTableData);
	BlockBreak->Destroy();
	return IBreakableInterface::OnBlockBreak_Implementation(InstigatorCharacter, BlockBreak);
}

bool ABlockEntityActor::OnBlockPlace_Implementation(AActor* InstigatorCharacter, AActor* BlockPlaced)
{
	// Event already called by UBuildModuleManager::PlaceBuildPreview()
	return IBreakableInterface::OnBlockPlace_Implementation(InstigatorCharacter, BlockPlaced);
}

bool ABlockEntityActor::OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableDataContext)
{
	if (bDropSelf)
	{
		const FTransform SpawnTransform(
			this->GetActorLocation() + this->GetActorUpVector() * 50);
		FVector LaunchDirection = this->GetActorUpVector() * 100 + FVector(0, 0, 50);
		FVector LaunchVelocity = LaunchDirection * 2;

		TObjectPtr<UItemStack> ItemStack = UItemStack::CreateItemStackFromMaterial(this->GetWorld(), Material, 1);
		GetGameEventHandler()->OnItemDropEvent(ItemStack, this);
		// TODO: Change this instigator to player or else not block itself
		UItemEntityUtilityLibrary::DropItemInWorld(this, ItemStack, SpawnTransform, LaunchVelocity);
	}
	return IBreakableInterface::OnBlockDrop_Implementation(Block, DropTableDataContext);
}
