// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Item/ItemStack.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "CharmingCraft/Core/Skill/Actions/ActionActor/BaseActionActor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ActionCastLib.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "ActionCastLibarary"))
class CHARMINGCRAFT_API UActionCastLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Physics")
	static FRotator GetRotationBetweenTwoPoints(FVector StartPoint, FVector EndPoint)
	{
		FVector ToTarget = EndPoint - StartPoint;
		ToTarget.Normalize();

		const FRotator Rotation = ToTarget.Rotation();
		return Rotation;
	}

	/*!
	 * Spawn Action Actor (or Entity) that represent different skills, use need to provide
	 * ActionActorData that contain different Actions that could triggered in different event
	 * For example, user could pass an burning Action that contained apply buff to target. This
	 * Action could pass into OnHitCastAction and the action will cast when Action Entity hit
	 * some target
	 * @param ActionActorTransform The location and rotation
	 * @param ActionActorData The essential data that describe the behaviour of Action Entity
	 * @param ActionActorClass The Class you would create, it will use different InjectActionData Methods
	 * @param CollisionHandlingOverride Collied
	 * @return The Action Entity with modified data
	 */
	UFUNCTION(BlueprintCallable, Category = "Action Actor")
	static ABaseActionActor* SpawnActionActor(FTransform ActionActorTransform,
	                                          FActionActorData ActionActorData,
	                                          TSubclassOf<ABaseActionActor> ActionActorClass,
	                                          ESpawnActorCollisionHandlingMethod CollisionHandlingOverride)
	{
		TObjectPtr<ABaseActionActor> ActionActor = Cast<ABaseActionActor>(
			UGameplayStatics::BeginDeferredActorSpawnFromClass(ActionActorData.Parent, ActionActorClass,
			                                                   ActionActorTransform, CollisionHandlingOverride));
		ActionActor->InjectActionData(ActionActorData);
		UGameplayStatics::FinishSpawningActor(ActionActor, ActionActorTransform);
		return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Action Actor")
	static UNativeAction* GetItemActionsByType(UItemStack* ItemStack, APawn* Owner, EItemDynamicSkillSlot ActionType)
	{
		if (!(ItemStack && Owner))
		{
			return nullptr;
		}
		TObjectPtr<UDActionComponent> ActionComponent = Cast<UDActionComponent>(
			Owner->GetComponentByClass(UDActionComponent::StaticClass()));
		for (const UNativeAction* Action : ActionComponent->Actions)
		{
			if (Action == ItemStack->ItemMeta->BindItemDynamicSkill.Find(ActionType)->Get())
			{
				return ItemStack->ItemMeta->BindItemDynamicSkill.Find(ActionType)->Get();
			}
		}
		return nullptr;
	}
};
