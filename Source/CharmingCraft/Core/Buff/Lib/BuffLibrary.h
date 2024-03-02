// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Attribute/FHitData.h"
#include "CharmingCraft/Core/Buff/BuffHandlerComponent.h"
#include "CharmingCraft/Core/Buff/BuffInfo.h"
#include "CharmingCraft/Core/Buff/UBuffData.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BuffLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "BuffFactoryLibrary"))
class CHARMINGCRAFT_API UBuffLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Buff Creation")
	static UBuffInfo* CreateBuffInstanceDetailed(TSubclassOf<UBuffData> BuffDataClass, APawn* BuffInstigator,
	                                             APawn* BuffTarget, FHitData HitData,
	                                             TMap<FName, int32> InternalData, int32 MaxStack, int32 InitialStack,
	                                             bool bIsForever,
	                                             float Duration,
	                                             float TickTime)
	{
		UBuffData* CreatedBuffData;
		if (BuffTarget) // Specify the parent of the buff instance object
		{
			CreatedBuffData = NewObject<UBuffData>(BuffTarget, BuffDataClass);
		}
		else // not Specify the parent of the buff instance object, for example AOE
		{
			CreatedBuffData = NewObject<UBuffData>(GetTransientPackage(), BuffDataClass);
		}

		CreatedBuffData->MaxStack = MaxStack;
		CreatedBuffData->bIsForever = bIsForever;
		CreatedBuffData->Duration = Duration;
		CreatedBuffData->InternalValue.Append(InternalData); // Append Internal Data

		UBuffInfo* CreatedBuffInfo = NewObject<UBuffInfo>(CreatedBuffData, UBuffInfo::StaticClass());
		CreatedBuffInfo->BuffData = CreatedBuffData;
		CreatedBuffInfo->Instigator = BuffInstigator;
		CreatedBuffInfo->Target = BuffTarget;
		//CreatedBuffInfo->CurrentStack = InitialStack;

		UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create BuffInfo: %s"),
		       *CreatedBuffInfo->BuffData->BuffName.ToString());

		return CreatedBuffInfo;

		// UE_LOG(LogChamingCraftBuff, Error, TEXT("[x] Fail To Create BuffInfo:"));
		// return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Buff Creation")
	static UBuffInfo* CreateBuffInstance(TSubclassOf<UBuffData> BuffDataClass, APawn* BuffInstigator,
	                                     APawn* BuffTarget, FHitData HitData
	)
	{
		UBuffData* CreatedBuffData;
		if (BuffTarget) // Specify the parent of the buff instance object
		{
			CreatedBuffData = NewObject<UBuffData>(BuffTarget, BuffDataClass);
		}
		else // not Specify the parent of the buff instance object, for example AOE
		{
			CreatedBuffData = NewObject<UBuffData>(GetTransientPackage(), BuffDataClass);
		}

		UBuffInfo* CreatedBuffInfo = NewObject<UBuffInfo>(CreatedBuffData, UBuffInfo::StaticClass());

		CreatedBuffInfo->BuffData = CreatedBuffData;
		CreatedBuffInfo->Instigator = BuffInstigator;
		CreatedBuffInfo->Target = BuffTarget;


		UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create BuffInfo: %s"),
		       *CreatedBuffInfo->BuffData->BuffName.ToString());
		return CreatedBuffInfo;

		// UE_LOG(LogChamingCraftBuff, Error, TEXT("[x] Fail To Create BuffInfo:"));
		// return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "Buff Add")
	static bool AddBuffToTarget(UBuffInfo* BuffInstance, APawn* Target, FHitData HitData)
	{
		BuffInstance->Target = Target;
		TObjectPtr<UBuffHandlerComponent> TargetBuffHandlerComponent = Cast<UBuffHandlerComponent>(
			Target->GetComponentByClass(
				UBuffHandlerComponent::StaticClass()));

		if (TargetBuffHandlerComponent)
		{
			TargetBuffHandlerComponent->AddBuff(BuffInstance, HitData);
			UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Add Buff [%s] to Target [%s]"),
			       *BuffInstance->BuffData->BuffName.ToString(), *Target->GetName());
			return true;
		}
		UE_LOG(LogChamingCraftBuff, Error, TEXT("[x] Fail To Add Buff [%s] to Target [%s]"),
		       *BuffInstance->BuffData->BuffName.ToString(), *Target->GetName());
		UE_LOG(LogChamingCraftBuff, Error, TEXT("	 [I] Because Target [%s] Do not have BuffHandlerComponent"),
		       *Target->GetName());
		return false;
		return true;
	}
};
