// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Interface/UBreakable.h"
#include "CharmingCraft/Core/Builds/Interface/UVisualEnhancement.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "BlockEntityActor.generated.h"
class UBoxComponent;

UENUM(BlueprintType)
enum class EBlockManipulationType: uint8
{
	BUILD_SYSTEM UMETA(DisplayName = "Build System"),
	GENERATED UMETA(DisplayName = "Generated")
};

UCLASS()
class CHARMINGCRAFT_API ABlockEntityActor : public AInteractObject, public IBreakableInterface,
                                            public IVisualEnhancementInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockEntityActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DisableBlockCollision();
	UFUNCTION(BlueprintCallable)
	void EnableBlockCollision();
	// Collision box that use for build system collision check and in game collision
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	// Scale box used for visual enhance, usually invisible in World
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Scale")
	TObjectPtr<UStaticMeshComponent> Scale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Drop Table")
	TObjectPtr<UDropTableData> DropTableData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Drop Table")
	bool bDropSelf = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsPlaced = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCollied = false;

	// 处理开始重叠的逻辑
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
	/*!
	 * Visual experience enhance: update the outlook of block base on their collision state
	 * , usually called by BuildModuleManager, In default the scale should invisible in World
	 * DisablePreviewScaleBox()
	 * @param NewType Updated Collision Type
	 * @param PlaceValidation The Data that contain loaded Material that prepare apply on scale box
	 */
	UFUNCTION(BlueprintCallable)
	void ChangeValidationCollidedType(EBuildCollidedType NewType, const FPlaceValidation& PlaceValidation);
	UFUNCTION(BlueprintCallable)
	void EnablePreviewScaleBox();
	UFUNCTION(BlueprintCallable)
	void DisablePreviewScaleBox();

public:
	// Life cycle of On Block place
	// Start block function at this place
	virtual bool OnBlockBreak_Implementation(ACharacter* Instigator, AActor* BlockBreak
	) override;
	virtual bool OnBlockPlace_Implementation(ACharacter* Instigator, AActor* BlockPlaced) override;

	virtual bool OnBlockDrop_Implementation(AActor* Block, UDropTableData* DropTableDataContext) override;
};
