// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"

#include "DGameplayInterface.h"


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

void UDInteractionComponent::PrimaryInteract()
{
	/*!
	 *	LineTrace从世界发射一个虚拟线,到达目的地,检索穿过的所有目标
	 *	FHitResult Hit 命中结果集
	 */
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); //搜索到WorldDynamic类型的目标就停止

	//GetOwner() 直接返回这个ActorComponent绑定的Actor,这里是我们的角色
	AActor* MyOwner = GetOwner();


	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);


	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams); //这个函数后填满了Hit信息
	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UDGameplayInterface>()) //注意 Check Implements 泛型是UDGameplayInterface, UE生成的接口
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IDGameplayInterface::Execute_Interact(HitActor, MyPawn); // 注意 调用的时候是使用的我们自己写的接口而不是 UE生产的
		}
	}
}
