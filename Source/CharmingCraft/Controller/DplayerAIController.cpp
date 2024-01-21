// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "DPlayerAIController.h"
#include "CharmingCraft/Core/Interact/DInteractionComponent.h"
#include "Navigation/PathFollowingComponent.h"

/*!
 * 
 * @param  RequestID 路径任务的ID
 * @param  Result 该路径任务的返回结果struct
 */
void ADPlayerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//Super::OnMoveCompleted(RequestID, Result);
	ADCharacter* Player = Cast<ADCharacter>(GetPawn());

	//TODO: SEVER! YOU MUST FIX DOUBLE INTERACT BUG
	
	// 如果被打断,没有成功
	if (!Result.IsSuccess())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interrupted! %s"), *Result.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Interrupted while moving ADPlayerAIController::OnMoveCompleted"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enter ADPlayerAIController::OnMoveCompleted"));
		Player->InteractionComp->ExecuteInteractAction();
		//TargetActor = nullptr; // Reset the target actor
	}
}
