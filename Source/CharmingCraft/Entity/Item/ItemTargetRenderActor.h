// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropItem.h"
#include "GameFramework/Actor.h"
#include "ItemTargetRenderActor.generated.h"

UCLASS()
class CHARMINGCRAFT_API AItemTargetRenderActor : public ADropItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemTargetRenderActor();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USceneCaptureComponent2D* SceneCaptureComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UTextureRenderTarget2D* TextureRenderTarget2D;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMaterialInstanceDynamic* OutPutMaterialInstanceDynamic;

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
