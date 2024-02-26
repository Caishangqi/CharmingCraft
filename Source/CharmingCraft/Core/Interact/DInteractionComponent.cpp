// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"
#include "DCharacter.h"
#include "../Interface/DGameplayInterface.h"
#include "CharmingCraft/CharmingCraft.h"
#include "CharmingCraft/Controller/DPlayerAIController.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Core/Entity/Creature/Creature.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Interface/InteractObject.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "../Core/Container/Inventory/InventoryComponent.h"


// Sets default values for this component's properties
UDInteractionComponent::UDInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InteractTag = FGameplayTag::RequestGameplayTag(FName("Status.Interacting"));
	// ...
}


// Called when the game starts
void UDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ADCharacter>(GetOuter());
	// 初始化AI控制器 负责玩家交互过程中的移动
}


// Called every frame
void UDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UDInteractionComponent::PrimaryInteract(AActor* HitActor, FVector HitLocation)
{
	//AIController->TargetActor = nullptr;
	UE_LOG(LogChamingCraftComponents, Warning, TEXT("[+] UDInteractionComponent::PrimaryInteract"));
	FGameplayTag StandbyTag = FGameplayTag::RequestGameplayTag(FName("Status.Standby"));
	Player->ActionComponent->ActiveGamePlayTags.AddTag(InteractTag);

	if (Player->ActionComponent->ActiveGamePlayTags.HasTag(StandbyTag))
	{
		Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
		Player->ActionComponent->MainHandAction();
	}

	if (HitActor)
	{
		/*
		 * AIController 的实例化首先不能在角色构造器中, 因为他需要在世界中生成
		 * 你需要在玩家对象生成后在玩家类的BeingPlay()中初始化AI控制器,由于玩家
		 * 实例化和InteractComponent是同步的,所以你在InteractComponent获取
		 * 玩积类上的AIController会空指针,因为这时没有触发玩家类上的BeingPlay()
		 */
		if (HitActor->Implements<UDGameplayInterface>() && Cast<AInteractObject>(HitActor))
		//注意 Check Implements 泛型是UDGameplayInterface, UE生成的接口
		{
			AInteractObject* CastedObject = Cast<AInteractObject>(HitActor);
			//UE_LOG(LogTemp, Warning, TEXT("The Actor's range is %d"), CastedObject->MinimumInteractRange);
			//计算玩家角色和这个Actor之间的距离
			float Distance = FVector::DistXY(Player->GetActorLocation(), HitActor->GetActorLocation());
			//UE_LOG(LogTemp, Warning, TEXT("The Distance between is %f"), Distance);

			/* 如果是执行攻击操作则开始判断人物身上的 AttackRange 属性 */
			if (CastedObject->bIsAllowToDamage)
			{
				if (Distance < Player->AttributeComp->AttackRange)
				{
					/* 转向 */
					Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
					Player->ActionComponent->MainHandAction();
					//return true; // If do not need extra MoveTo(), then return true
				}

				// 如果这个移动Path没有被玩家自己打断，则到达目标Actor后执行

				// 执行动作
				AIController->TargetActor = HitActor;

				// 使用AI控制器移动Pawn
				AIController->MoveToActor(HitActor, Player->AttributeComp->AttackRange, true, true, false,
				                          nullptr,
				                          false);
				DrawDebugLine(Player->GetWorld(), HitActor->GetActorLocation(), HitActor->GetActorLocation(),
				              FColor::Yellow, false, 2, ECC_Visibility,
				              20.0f);
			}

			// 如股玩家的距离在可交互距离内, 则不用走过去执行动作,直接执行
			if (Distance < CastedObject->MinimumInteractRange)
			{
				IDGameplayInterface::Execute_Interact(HitActor, Player);
				Cast<ADCharacter>(GetOwner())->InventoryComponent->OnItemInteract(HitActor, Player);
			}
			else
			{
				// 给AI控制器类里面设置点击的目标, 传参到这个类
				AIController->TargetActor = HitActor;
				// 使用AI控制器移动Pawn
				AIController->MoveToActor(HitActor, CastedObject->MinimumInteractRange, true, true, true,
				                          nullptr, true);
			}
		}

		/* Handle Hit Creature Logic */
		if (HitActor->Implements<UDamageable>())
		{
			return ExecuteInteractWithCreature(HitActor);
		}
	}
	Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
	return true;
}


bool UDInteractionComponent::ExecuteInteractAction()
{
	UE_LOG(LogChamingCraftComponents, Warning, TEXT("[+] UDInteractionComponent::ExecuteInteractAction"));
	/* Handle Interact Object Logic */
	if (AIController->TargetActor->Implements<UDGameplayInterface>() && AIController->TargetActor->IsA(
		AInteractObject::StaticClass()))
	{
		if (Cast<AInteractObject>(AIController->TargetActor.Get())->bIsAllowToDamage)
		{
			Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
			Player->ActionComponent->MainHandAction();
			return false;
		}
		IDGameplayInterface::Execute_Interact(AIController->TargetActor.Get(), Player);
		Player->InteractionComp->OnItemInteract(AIController->TargetActor.Get(), Player);
	}
	/* Handle Creature Interact */
	else if (AIController->TargetActor.IsValid() && AIController->TargetActor->Implements<UDamageable>())
	{
		Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
		Player->ActionComponent->MainHandAction();

		/* This should have future NPC interact, not damage them, interact with them */

		return false;
	}
	Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
	return true;
}


void UDInteractionComponent::LineTracingInteract() const
{
	/*!
	 *	LineTrace从世界发射一个虚拟线,到达目的地,检索穿过的所有目标
	 *	FHitResult Hit 命中结果集
	 */

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); //搜索到WorldDynamic类型的目标就停止

	//GetOwner() 直接返回这个ActorComponent绑定的Actor,这里是我们的角色
	AActor* MyOwner = GetOwner();


	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);


	/*
	 *	线性追踪实现方法 I
	 */

	/*
	//是否击中,这个也可以不需要返回值也能正常运行
	FHitResult Hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	*/

	/* 线性追踪实现方法 I
	 * AActor* HitActor = Hit.GetActor();
	 * if (HitActor)
	 * {
	 * if (HitActor->Implements<UDGameplayInterface>()) //注意 Check Implements 泛型是UDGameplayInterface, UE生成的接口
	 * 	{
	 * 	APawn* MyPawn = Cast<APawn>(MyOwner);
	 * 	IDGameplayInterface::Execute_Interact(HitActor, MyPawn); // 注意 调用的时候是使用的我们自己写的接口而不是 UE生产的
	 * 	}
	 * }
	 */

	/*
	 *	球型追踪实现方法 II
	 *	FQuat::Identity 意思为没有旋转
	 */
	float Radius = 30.0f;
	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams,
	                                                       Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UDGameplayInterface>()) //注意 Check Implements 泛型是UDGameplayInterface, UE生成的接口
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IDGameplayInterface::Execute_Interact(HitActor, MyPawn); // 注意 调用的时候是使用的我们自己写的接口而不是 UE生产的
				break; //碰到第一个可交互物品就跳出循环
			}
			//每次球体命中就把这个球画出来
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
		}
	}


	//这个函数后填满了Hit信息


	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

void UDInteractionComponent::OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator)
{
	Player->InventoryComponent->OnItemInteract(TargetActor, Instigator);
	UE_LOG(LogTemp, Warning, TEXT("Call Back from UDInteractionComponent::OnItemInteract"));
}

bool UDInteractionComponent::ExecuteInteractWithCreature(AActor* TargetActor)
{
	TObjectPtr<ACreature> TargetCreature = Cast<ACreature>(TargetActor);
	float Distance = FVector::DistXY(Player->GetActorLocation(), TargetCreature->GetActorLocation());
	if (Distance < Player->AttributeComp->AttackRange)
	{
		/* 转向 */
		Player->ActionComponent->ActiveGamePlayTags.RemoveTag(InteractTag);
		Player->ActionComponent->MainHandAction();
		return true;
	}
	else
	{
		// 给AI控制器类里面设置点击的目标, 传参到这个类
		AIController->TargetActor = TargetCreature.Get();
		AIController->MoveToActor(TargetCreature, Player->AttributeComp->AttackRange, true, true, true,
		                          nullptr, true);
		return false;
	}
}
