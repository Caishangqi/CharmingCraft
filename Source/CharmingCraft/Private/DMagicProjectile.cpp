// Fill out your copyright notice in the Description page of Project Settings.


#include "DMagicProjectile.h"

#include "DAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADMagicProjectile::ADMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->SetEnableGravity(false);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	// 当弹道的球状Component碰撞到角色时对健康值做出改变
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADMagicProjectile::OnActorOverlap);
}

// Called when the game starts or when spawned
void ADMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ADMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	//Check the other actor, collision one is not null
	if (OtherActor)
	{
		// 找到击中的组件并且在这个组件身上找到UDAttributeComponent这个组件
		UDAttributeComponent* AttributeComp = Cast<UDAttributeComponent>(
			OtherActor->GetComponentByClass(UDAttributeComponent::StaticClass())); // StaticClass() 允许传入类作为参数
		// 假如打到墙壁, 但是墙壁没有这个类型的Component,因此还需要一个if判断
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f); // -20 血

			Destroy();
		}
	}
}

// Called every frame
void ADMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
