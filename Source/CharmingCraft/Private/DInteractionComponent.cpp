// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"

#include "AIController.h"
#include "DCharacter.h"
#include "../Interface/DGameplayInterface.h"
#include "CharmingCraft/Controller/DPlayerController.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"


// Sets default values for this component's properties
UDInteractionComponent::UDInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDInteractionComponent::PrimaryInteract() const
{
	AActor* MyOwner = GetOwner();
	APlayerController* Controller = Cast<APlayerController>(MyOwner->GetInstigatorController());
	float MouseX, MouseY;
	Controller->GetMousePosition(MouseX, MouseY);

	// 将鼠标位置转换为世界空间的射线
	FHitResult HitResult;
	// 将鼠标位置转换为世界空间的射线
	FVector WorldLocation, WorldDirection;
	Controller->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);


	// 进行射线投射
	FVector StartLocation = WorldLocation;
	FVector EndLocation = StartLocation + WorldDirection * 10000.0f; // 你可以根据需要调整这个值
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);

	// 如果射线击中了一个Actor，那么获取这个Actor
	AActor* HitActor = HitResult.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UDGameplayInterface>() && Cast<ADAbstractInterObjectPrototype>(HitActor))
		//注意 Check Implements 泛型是UDGameplayInterface, UE生成的接口
		{
			ADAbstractInterObjectPrototype* CastedObject = Cast<ADAbstractInterObjectPrototype>(HitActor);
			UE_LOG(LogTemp, Warning, TEXT("The Actor's range is %d"), CastedObject->MinimumInteractRange);
			//计算玩家角色和这个Actor之间的距离
			float Distance = FVector::DistXY(MyOwner->GetActorLocation(), HitActor->GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("The Distance between is %f"), Distance);
			if (Distance < CastedObject->MinimumInteractRange)
			{
				ACharacter* Character = Cast<ACharacter>(MyOwner);
				// TODO 在范围内阻止玩家移动
				ADPlayerController* c = Cast<ADPlayerController>(Character->Controller);

				// 执行交互操作
				IDGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
			}
		}
	}
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
