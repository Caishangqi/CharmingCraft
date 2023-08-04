// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerAIController.h"
#include "CharmingCraft/Interface/DAbstractInterObjectPrototype.h"
#include "CharmingCraft/Interface/DGameplayInterface.h"
#include "Navigation/PathFollowingComponent.h"

/*!
 * 
 * @param  RequestID 路径任务的ID
 * @param  Result 该路径任务的返回结果struct
 */
void ADPlayerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	// 如果被打断,没有成功
	if (!Result.IsSuccess())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interrupted while moving ADPlayerAIController::OnMoveCompleted"));
		TargetActor = nullptr; //释放资源
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter ADPlayerAIController::OnMoveCompleted"));
		if (TargetActor.IsValid() && TargetActor->Implements<UDGameplayInterface>() && Cast<
			ADAbstractInterObjectPrototype>(TargetActor.Get())) //弱指针解引
		{
			IDGameplayInterface::Execute_Interact(TargetActor.Get(), Cast<APawn>(GetPawn()));
		}
		TargetActor = nullptr; // Reset the target actor
	}
}
