// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "DInteractionComponent.h"
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
			// FIXME: 如果玩家成功交互物品,由AI控制器触发 交互组件上的 OnItemInteract()
			if (const ADCharacter* Player = Cast<ADCharacter>(GetPawn()))
			{
				/*
				 * 设计上的缺陷,这个其实最好由物品发出或者Interact组件本身
				 */
				Player->InteractionComp->OnItemInteract(TargetActor.Get(), Cast<APawn>(GetPawn()));
			}
		}
		TargetActor = nullptr; // Reset the target actor
	}
}
