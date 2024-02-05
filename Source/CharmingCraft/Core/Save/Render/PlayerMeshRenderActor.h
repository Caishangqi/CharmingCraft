// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPlayerPreviewLocation.h"
#include "Animation/SkeletalMeshActor.h"
#include "PlayerMeshRenderActor.generated.h"


class UGameSaveManager;
class UMaterial;

UCLASS(Blueprintable)
class CHARMINGCRAFT_API APlayerMeshRenderActor : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerMeshRenderActor();

	UPROPERTY()
	TObjectPtr<UMaterial> PreviewMaterial;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerPreviewLocation PreviewLocation;
	UPROPERTY()
	TObjectPtr<UGameSaveManager> GameSaveManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HideActor();
	UFUNCTION(BlueprintCallable)
	void ShowActor();
	UFUNCTION(BlueprintCallable)
	bool UpdatePreviewBaseSaveManager();

	bool IsPreviewLocationValidSlot();
};
