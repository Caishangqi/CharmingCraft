// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTargetRenderActor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
AItemTargetRenderActor::AItemTargetRenderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	DropIconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropIconMesh"));
	DropIconMesh->SetupAttachment(RootComponent); // 附加到Root组件
	DropModelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DropModelMesh"));
	DropModelMesh->SetupAttachment(RootComponent); //
	FRotator DropIconRotation = FRotator(0.0f, 180.0f, 0.0f); // Pitch, Yaw, Roll
	FVector DropIconLocation = FVector(0.0f, 0.0f, 8.0f); // X, Y, Z
	DropIconMesh->SetRelativeLocation(DropIconLocation);
	DropIconMesh->SetRelativeRotation(DropIconRotation);

	PrimaryActorTick.bCanEverTick = true;
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
	SceneCaptureComponent->SetupAttachment(RootComponent);
	SceneCaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	SceneCaptureComponent->OrthoWidth = 164;
	SceneCaptureComponent->bCaptureEveryFrame = false;
	SceneCaptureComponent->bCaptureOnMovement = true;
	SceneCaptureComponent->ShowFlags.SetLighting(false);
	SceneCaptureComponent->bAlwaysPersistRenderingState = true;
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActorComp"));
	ChildActorComponent->SetupAttachment(RootComponent);
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
	TextureRenderTarget2D = CreateDefaultSubobject<UTextureRenderTarget2D>("TextureRenderTarget2D");
	TextureRenderTarget2D->InitCustomFormat(512, 512, PF_FloatRGBA, false);
	SceneCaptureComponent->TextureTarget = TextureRenderTarget2D;
}

// Called when the game starts or when spawned
void AItemTargetRenderActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("(!) AItemTargetRenderActor::BeginPlay()"))
	// SceneCaptureComponent->ShowOnlyComponent(DropModelMesh);
	// SceneCaptureComponent->ShowOnlyComponent(DropIconMesh);
	// 把渲染的 Texture 2D传给 自身存储的Texture
	SceneCaptureComponent->CaptureScene();


	if (CachedMaterial)
	{
		OutPutMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(CachedMaterial, this);
		OutPutMaterialInstanceDynamic->SetTextureParameterValue(FName("InputRenderTarget"), TextureRenderTarget2D);
		UE_LOG(LogTemp, Warning, TEXT("(!) AItemTargetRenderActor Successfully Add DMI"))
	}
}

// Called every frame
void AItemTargetRenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
};
