// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTargetRenderActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API AItemTargetRenderActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemTargetRenderActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropIconMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DropModelMesh;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UTextureRenderTarget2D* TextureRenderTarget2D;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMaterialInstanceDynamic* OutPutMaterialInstanceDynamic;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UChildActorComponent* ChildActorComponent;

private:
	UPROPERTY(VisibleAnywhere)
	UMaterial* CachedMaterial = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
