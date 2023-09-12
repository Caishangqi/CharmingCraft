// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTargetRenderActor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
AItemTargetRenderActor::AItemTargetRenderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
	SceneCaptureComponent->SetupAttachment(RootComponent);
	SceneCaptureComponent->SetRelativeRotation(FRotator3d(0.0, -10.0, -120));
	SceneCaptureComponent->SetRelativeLocation(FVector3d(50.0, 90.0, 60.0));
	SceneCaptureComponent->bCaptureEveryFrame = false;
	SceneCaptureComponent->bCaptureOnMovement = true;
	SceneCaptureComponent->ShowFlags.SetLighting(true);
	UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(this->GetRootComponent());

	if (PrimComp)
	{
		PrimComp->SetSimulatePhysics(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT(
		"/Script/Engine.Material'/Game/CharmingCraft/Item/ItemTest/TextureRenderTarget2D_Mat.TextureRenderTarget2D_Mat'"));
	if (FoundMaterial.Succeeded())
	{
		CachedMaterial = FoundMaterial.Object;
	}
}

// Called when the game starts or when spawned
void AItemTargetRenderActor::BeginPlay()
{
	Super::BeginPlay();
	SceneCaptureComponent->ShowOnlyComponent(DropModelMesh);
	SceneCaptureComponent->ShowOnlyComponent(DropIconMesh);
	// 把渲染的 Texture 2D传给 自身存储的Texture
	SceneCaptureComponent->CaptureScene();
	TextureRenderTarget2D = SceneCaptureComponent->TextureTarget;


	if (CachedMaterial)
	{
		OutPutMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(CachedMaterial, this);
		OutPutMaterialInstanceDynamic->SetTextureParameterValue(FName("InputRenderTarget"), TextureRenderTarget2D);
	}
}

// Called every frame
void AItemTargetRenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
};
