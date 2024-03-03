// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceEntityGeometryActor.h"

#include "CharmingCraft/Core/Log/Logging.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/KismetMaterialLibrary.h"


// Sets default values
AResourceEntityGeometryActor::AResourceEntityGeometryActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AResourceEntityGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	MaterialInstanceDynamic = GeometryCollectionComponent->CreateDynamicMaterialInstance(
		0, GeometryCollectionComponent->GetMaterial(0));
	// 设置一个倒计时定时器
	GetWorld()->GetTimerManager().SetTimer(InternalDestroyTimer, this,
	                                       &AResourceEntityGeometryActor::DestroyResourceEntityGeometryActor,
	                                       LifeTime, false);
	GetWorld()->GetTimerManager().SetTimer(InternalDecorationTimer, this,
	                                       &AResourceEntityGeometryActor::ApplyResourceEntityDecoration,
	                                       0.5, true);
}

// Called every frame
void AResourceEntityGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AResourceEntityGeometryActor::DestroyResourceEntityGeometryActor()
{
	this->Destroy();
}

void AResourceEntityGeometryActor::ApplyResourceEntityDecoration()
{
	float OpacityValue = 0.0f;
	bool bFoundParameter = false;
	FMaterialParameterInfo ParamInfo(FName("Opacity"));

	if (MaterialInstanceDynamic != nullptr)
	{
		bFoundParameter = MaterialInstanceDynamic->GetScalarParameterValue(ParamInfo, OpacityValue);
		if (bFoundParameter)
		{
			UE_LOG(LogChamingCraftCraftResource, Display,
			       TEXT("[✅️]  Apply ApplyResourceEntityDecoration to Resource"));
			OpacityValue -= 0.2f;
			MaterialInstanceDynamic->SetScalarParameterValue(FName("Opacity"), bFoundParameter);
			GeometryCollectionComponent->SetMaterial(0, MaterialInstanceDynamic);
		}
		else
		{
			// 没有找到Opacity参数
			UE_LOG(LogChamingCraftCraftResource, Error,
			       TEXT("[❌]  Error to ApplyResourceEntityDecoration to Resource"));
		}
	}
}
