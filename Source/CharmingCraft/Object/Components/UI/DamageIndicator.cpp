// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageIndicator.h"


// Sets default values for this component's properties
UDamageIndicator::UDamageIndicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UDamageIndicator::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UDamageIndicator::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	// UE_LOG(LogTemp, Error, TEXT("UDamageIndicator::UDamageIndicator() Destroy"));
}


// Called every frame
void UDamageIndicator::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UUserWidget* UDamageIndicator::GetWidgetInstance()
{
	// 确保 WidgetClass 被正确设置
	if (WidgetClass == nullptr)
	{
		return nullptr;
	}

	// 这里假设你的组件是附加到 Actor 的，
	// 并且该 Actor 拥有有效的 World 上下文。
	UWorld* World = GetOwner()->GetWorld();
	//UUserWidget * Temp = CreateWidget<UUserWidget>(World, WidgetClass, "DamageIndicator");


	return DuplicateObject(GetWidget(), this, "DamageIndicator");
}
