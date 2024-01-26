// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffHandlerComponent.h"

#include "CharmingCraft/Core/Log/Logging.h"

// 定义比较函数
struct FBuffInfoPriorityComparer
{
	bool operator()(const TObjectPtr<UBuffInfo>& A, const TObjectPtr<UBuffInfo>& B) const
	{
		return A->BuffData->Priority < B->BuffData->Priority;
	}
};


UBuffHandlerComponent::UBuffHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UBuffInfo* UBuffHandlerComponent::CreateBuffInfo(TSubclassOf<UBuffData> BuffDataClass, APawn* BuffInstigator,
                                                 APawn* BuffTarget, bool AddAfterCreate, FHitData HitData,
                                                 TMap<FName, int32> InternalData)
{
	UBuffData* CreatedBuffData = NewObject<UBuffData>(this, BuffDataClass);
	UBuffInfo* CreatedBuffInfo = NewObject<UBuffInfo>(this, UBuffInfo::StaticClass());

	CreatedBuffData->InternalValue.Append(InternalData); // Append Internal Data

	CreatedBuffInfo->BuffData = CreatedBuffData;
	CreatedBuffInfo->Instigator = BuffInstigator;
	CreatedBuffInfo->Target = BuffTarget;

	if (CreatedBuffInfo)
	{
		if (AddAfterCreate)
		{
			UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create and Add BuffInfo: %s"),
			       *CreatedBuffInfo->BuffData->BuffName.ToString());
			AddBuff(CreatedBuffInfo, HitData);
		}
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create BuffInfo: %s"),
		       *CreatedBuffInfo->BuffData->BuffName.ToString());
		return CreatedBuffInfo;
	}
	UE_LOG(LogChamingCraftBuff, Error, TEXT("[x] Fail To Create BuffInfo:"));
	return nullptr;
}

void UBuffHandlerComponent::AddBuff(UBuffInfo* BuffInfo, FHitData HitData)
{
	TObjectPtr<UBuffInfo> SearchedBuff = SearchBuff(BuffInfo->BuffData->Id);
	if (SearchedBuff)
	{
		// Buff Already in the List
		if (SearchedBuff->CurrentStack < SearchedBuff->BuffData->MaxStack)
		{
			SearchedBuff->CurrentStack++;
			UpdateBuffDuration(SearchedBuff);
			BuffInfo->BuffData->OnCreate.GetDefaultObject()->Apply(BuffInfo, HitData);
		}
		// Buff Already in the List and Current stack equal max stack allowed
		if (SearchedBuff->CurrentStack == SearchedBuff->BuffData->MaxStack)
		{
			UpdateBuffDuration(SearchedBuff);
			/* should not call Apply()*/
			//BuffInfo->BuffData->OnCreate.GetDefaultObject()->Apply(BuffInfo, HitData);
		}
	}
	else
	{
		// Buff Do not in the List
		BuffInfo->Duration = BuffInfo->BuffData->Duration;
		BuffInfo->BuffData->OnCreate.GetDefaultObject()->Apply(BuffInfo, HitData);
		BuffList.Add(BuffInfo);
		// Order the BuffList based on Priority
		BuffList.Sort(FBuffInfoPriorityComparer());

		// UI Envent: Add Buff that first time
		OnBuffAddToBuffList.Broadcast(BuffInfo, HitData);
	}
}

void UBuffHandlerComponent::UpdateBuffDuration(UBuffInfo* BuffInfo)
{
	switch (BuffInfo->BuffData->BuffTimeUpdate)
	{
	case EBuffTimeUpdate::Add:
		BuffInfo->Duration += BuffInfo->BuffData->Duration;
		break;
	case EBuffTimeUpdate::Replace:
		BuffInfo->Duration = BuffInfo->BuffData->Duration;
		break;
	}
}

void UBuffHandlerComponent::RemoveBuff(UBuffInfo* BuffInfo, FHitData HitData)
{
	switch (BuffInfo->BuffData->BuffRemoveStackUpdate)
	{
	case EBuffRemoveStackUpdate::Clear:
		BuffInfo->BuffData->OnRemove.GetDefaultObject()->Apply(BuffInfo, HitData);
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Remove BuffInfo: %s"), *BuffInfo->BuffData->BuffName.ToString());
		BuffInfo->OnBuffInfoRemoved.Broadcast(BuffInfo); // Broadcast Remove Event
		BuffList.Remove(BuffInfo);
		break;
	case EBuffRemoveStackUpdate::Reduce:
		BuffInfo->CurrentStack--;
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Reduce Stack BuffInfo: %s, Current Stack: %d"),
		       *BuffInfo->BuffData->BuffName.ToString(),
		       BuffInfo->CurrentStack);
		if (BuffInfo->BuffData->OnRemove)
		{
			BuffInfo->BuffData->OnRemove.GetDefaultObject()->Apply(BuffInfo, HitData);
		}
		if (BuffInfo->CurrentStack <= 0)
		{
			UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Remove BuffInfo Due to stack is 0: %s"),
			       *BuffInfo->BuffData->BuffName.ToString());
			BuffInfo->OnBuffInfoRemoved.Broadcast(BuffInfo); // Broadcast Remove Event
			BuffList.Remove(BuffInfo);
		}
		else
		{
			// Reset Buff Timer
			BuffInfo->Duration = BuffInfo->BuffData->Duration;
		}

		break;
	}
}

void UBuffHandlerComponent::BuffTickAndRemove(float DeltaTime)
{
	FHitData HitData;
	TArray<TObjectPtr<UBuffInfo>> PrepareDeleteBuffList;
	for (auto BuffInstance : BuffList)
	{
		if (BuffInstance->BuffData->OnTick != nullptr)
		{
			if (BuffInstance->TickTime < 0)
			{
				BuffInstance->BuffData->OnTick.GetDefaultObject()->Apply(BuffInstance, HitData);
				BuffInstance->TickTime = BuffInstance->BuffData->TickTime;
			}
			else
			{
				BuffInstance->TickTime -= DeltaTime; // TODO
			}
		}
		if (BuffInstance->Duration < 0)
		{
			PrepareDeleteBuffList.Add(BuffInstance);
		}
		else
		{
			BuffInstance->Duration -= DeltaTime;
		}
		
	}
	for (auto DeleteBuffList : PrepareDeleteBuffList)
	{
		RemoveBuff(DeleteBuffList, HitData);
	}
}


void UBuffHandlerComponent::Update(float DeltaTime)
{
	// Handle BuffTick
	BuffTickAndRemove(DeltaTime);
}

void UBuffHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Update(DeltaTime);
	//UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] TickDeltaTime: %f"), DeltaTime);
}

TObjectPtr<UBuffInfo> UBuffHandlerComponent::SearchBuff(int32 Id)
{
	for (TObjectPtr<UBuffInfo> BuffInfoInstance : BuffList)
	{
		if (BuffInfoInstance->BuffData->Id == Id)
		{
			return BuffInfoInstance;
		}
	}
	return nullptr;
}
