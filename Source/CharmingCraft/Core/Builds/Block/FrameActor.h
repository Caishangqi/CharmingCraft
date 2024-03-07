// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "GameFramework/Actor.h"
#include "FrameActor.generated.h"
class UBoxComponent;

UENUM(BlueprintType)
enum class EFrameType: uint8
{
	DESTROY UMETA(DisplayName = "Destroy")
};


UCLASS()
class CHARMINGCRAFT_API AFrameActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFrameActor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="FrameOutlineBox3D")
	TObjectPtr<UStaticMeshComponent> FrameOutlineBox3D;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="FrameOutline2D")
	TObjectPtr<UStaticMeshComponent> FrameOutline2D;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LoadedFrameAppearance")
	TMap<EFrameType, UMaterialInstance*> LoadedFrameAppearance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<AActor> ColliedActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFrameType CurrentFrameActorType = EFrameType::DESTROY;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="BuildModuleManager")
	TObjectPtr<UBuildModuleManager> BuildModuleManager;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Blueprintable, BlueprintNativeEvent)
	void SetFrameDestroyState();
};
