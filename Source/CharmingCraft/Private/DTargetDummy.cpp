// Fill out your copyright notice in the Description page of Project Settings.


#include "DTargetDummy.h"

// Sets default values
ADTargetDummy::ADTargetDummy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	// Trigger when health is changed (damaged/healing).
	AttributeComp->OnHealthChanged.AddDynamic(this, &ADTargetDummy::OnHealthChanged);
}

// Called when the game starts or when spawned
void ADTargetDummy::BeginPlay()
{
	Super::BeginPlay();
}

void ADTargetDummy::OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* OwningComp, float HewHealth,
                                    float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}

// Called every frame
void ADTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
