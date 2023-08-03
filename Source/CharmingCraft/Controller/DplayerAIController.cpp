// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerAIController.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "CharmingCraft/Interface/DGameplayInterface.h"
#include "Navigation/PathFollowingComponent.h"

void ADPlayerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	UE_LOG(LogTemp, Warning, TEXT("Enter ADPlayerAIController::OnMoveCompleted"));
	// 检查移动是否成功完成
	if (Result.Code == EPathFollowingResult::Success)
	{
		if (TargetActor.IsValid() && TargetActor->Implements<UDGameplayInterface>() && Cast<
			ADAbstractInterObjectPrototype>(TargetActor.Get()))
		{
			IDGameplayInterface::Execute_Interact(TargetActor.Get(), Cast<APawn>(GetPawn()));
		}
		TargetActor = nullptr; // Reset the target actor
	}
}
