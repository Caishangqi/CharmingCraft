// Fill out your copyright notice in the Description page of Project Settings.


#include "DMagicProjectile.h"

#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

class UDAttributeComponent;
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


	MoveComp->InitialSpeed = 1000.0f;
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;

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
	if (OtherActor && OtherActor != GetInstigator())
	{
		// 找到击中的组件并且在这个组件身上找到UDAttributeComponent这个组件
		UDAttributeComponent* AttributeComp = Cast<UDAttributeComponent>(
			OtherActor->GetComponentByClass(UDAttributeComponent::StaticClass())); // StaticClass() 允许传入类作为参数

		/* 比较不实用的方法,破坏了耦合性 */
		//static FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Status.Parrying");

		/* 如果玩家身上有标签,那么可以抵挡这次攻击 (建议方法)
		 * <see cref = "ADMagicProjectile.ParryTag" />
		 * 在这个方法中,我们可以暴露ParryTag,从而在编辑器中
		 * 编辑和操作
		 */
		UDActionComponent* ActionComp = Cast<UDActionComponent>(
			OtherActor->GetComponentByClass(UDActionComponent::StaticClass()));
		if (ActionComp && ActionComp->ActiveGamePlayTags.HasTag(ParryTag))
		{
			/* 反弹这次攻击,因为我们在 DMagicProjectiles.cpp 中设置了
			 * MoveComp->bRotationFollowsVelocity = true;,所以Rotation
			 * 也会跟随一起改变
			 */
			MoveComp->Velocity = -MoveComp->Velocity;
			/* 让这次攻击的煽动者成为玩家 */
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}


		// 假如打到墙壁, 但是墙壁没有这个类型的Component,因此还需要一个if判断
		if (AttributeComp)
		{
			// 调用 Actor(这个里是DCharactor也就是玩家)上的类型为UDAttributeComponent组件
			//AttributeComp->ApplyHealthChange(-20.0f); // -20 血
			// 因为这个 AttributeComp 实例化在玩家Actor中,所以改变AttributeComp中的Health就相当于改变了玩家的血量
			// 这是解耦很重要的一环

			/* Apply Damage Chain */
			AttributeComp->SubmitHitData(HitData);

			Destroy(); //完成任务后就可以摧毁这个弹射物了
		}
	}
}

// Called every frame
void ADMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
