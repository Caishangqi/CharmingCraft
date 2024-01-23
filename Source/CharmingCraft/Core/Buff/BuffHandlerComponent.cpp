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

UBuffInfo* UBuffHandlerComponent::CreateBuffInfo(TSubclassOf<UBuffData> BuffDataClass, AActor* BuffInstigator,
                                                 AActor* BuffTarget, bool AddAfterCreate, FHitData HitData)
{
	UBuffData* CreatedBuffData = NewObject<UBuffData>(this, BuffDataClass);
	UBuffInfo* CreatedBuffInfo = NewObject<UBuffInfo>(this, UBuffInfo::StaticClass());

	CreatedBuffInfo->BuffData = CreatedBuffData;
	CreatedBuffInfo->Instigator = BuffInstigator;
	CreatedBuffInfo->Target = BuffTarget;

	if (CreatedBuffInfo)
	{
		if (AddAfterCreate)
		{
			UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create and Add BuffInfo: %p"), CreatedBuffInfo);
			AddBuff(CreatedBuffInfo, HitData);
		}
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[+] Create BuffInfo: %p"), CreatedBuffInfo);
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
			switch (SearchedBuff->BuffData->BuffTimeUpdate)
			{
			case EBuffTimeUpdate::Add:
				SearchedBuff->Duration += SearchedBuff->BuffData->Duration;
				break;
			case EBuffTimeUpdate::Replace:
				SearchedBuff->Duration = SearchedBuff->BuffData->Duration;
				break;
			}
			SearchedBuff->BuffData->OnCreate.GetDefaultObject()->Apply(SearchedBuff, HitData);
		}
	}
	else
	{
		// Buff Do not in the List
		BuffInfo->Duration = BuffInfo->BuffData->Duration;
		//BuffInfo->TickTime = BuffInfo->BuffData->TickTime; // Add Buff wait timer countdown trigger onTick
		BuffInfo->BuffData->OnCreate.GetDefaultObject()->Apply(BuffInfo, HitData);
		BuffList.Add(BuffInfo);
		// Order the BuffList based on Priority
		BuffList.Sort(FBuffInfoPriorityComparer());
	}
}

void UBuffHandlerComponent::RemoveBuff(UBuffInfo* BuffInfo, FHitData HitData)
{
	switch (BuffInfo->BuffData->BuffRemoveStackUpdate)
	{
	case EBuffRemoveStackUpdate::Clear:
		BuffInfo->BuffData->OnRemove.GetDefaultObject()->Apply(BuffInfo, HitData);
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Remove BuffInfo: %p"), BuffInfo);
		BuffList.Remove(BuffInfo);
		break;
	case EBuffRemoveStackUpdate::Reduce:
		BuffInfo->CurrentStack--;
		UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Reduce Stack BuffInfo: %p, Current Stack: %d"), BuffInfo,
		       BuffInfo->CurrentStack);
		BuffInfo->BuffData->OnRemove.GetDefaultObject()->Apply(BuffInfo, HitData);
		if (BuffInfo->CurrentStack <= 0)
		{
			UE_LOG(LogChamingCraftBuff, Display, TEXT("[-] Remove BuffInfo Due to stack is 0: %p"), BuffInfo);
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
		for (auto DeleteBuffList : PrepareDeleteBuffList)
		{
			RemoveBuff(DeleteBuffList, HitData);
		}
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
