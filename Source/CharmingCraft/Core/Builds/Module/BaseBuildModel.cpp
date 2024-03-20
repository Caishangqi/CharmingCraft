// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuildModel.h"

#include "BuildModuleManager.h"
#include "CharmingCraft/Core/Builds/Block/FrameActor.h"
#include "CharmingCraft/Core/GameMode/PlayerMode/PlayerModeManager.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"

UBaseBuildModel::UBaseBuildModel()
{
	BuildModuleManager = Cast<UBuildModuleManager>(GetOuter());
}

bool UBaseBuildModel::OnPlace_Implementation(UObject* Instigator)
{
	return false;
}


bool UBaseBuildModel::ActivateBuildModel_Implementation(UObject* Instigator)
{
	bIsActivate = true;
	return StartTrace(Instigator);
}

bool UBaseBuildModel::DeactivateBuildModel_Implementation(UObject* Instigator)
{
	bIsActivate = false;
	return StopTrace(Instigator);
}

UWorld* UBaseBuildModel::GetWorld() const
{
	if (BuildModuleManager)
	{
		return BuildModuleManager->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

bool UBaseBuildModel::OnRemoveBuildModel_Implementation()
{
	/*
	*当你从TMap中Remove一个自定义UObject时，你只是从容器中移除了对该对象的引用，而没有立即销毁对象本身。如果没有其他地方引用这个UObject，它最终会在垃圾回收过程中被销毁。然而，这个过程是延迟发生的，不是立即执行的。

	委托与对象的生命周期是独立的。即使你从容器中移除了对象，只要这个对象还没有被垃圾回收，它的委托仍然是活跃的，并且如果触发了，那么相应的事件还是会被执行。这就是为什么你在Remove操作后仍然看到委托被触发的原因。

	要理解的关键点是：

	垃圾回收延迟：移除TMap中的对象并不会立即销毁对象，而是仅仅移除了对它的引用。如果没有其他引用指向该对象，它将在未来某个时刻由垃圾回收器销毁。

	委托活跃性：一个对象的委托在对象生命周期内都是活跃的，除非显式地解绑。这意味着，即便对象从逻辑上看似不再被使用（如从TMap中移除），只要对象还没有被销毁，其内部的委托如果被触发，相应的响应函数仍然会执行。

	因此，解决方法正如你所做的那样：在从容器中移除对象之前，先显式地解绑对象内部的所有委托。这样可以确保当对象不再被使用时，其内部的委托不会意外地被触发。这也是一个很好的实践，特别是在涉及到可能会被延迟销毁的对象时（如UObject），这样做可以避免潜在的错误和不确定性。
	*/
	TObjectPtr<UCharmingCraftInstance> GameInstance = Cast<UCharmingCraftInstance>(GetWorld()->GetGameInstance());
	GameInstance->PlayerModeManager->OnPlayerModeChangeDelegate.RemoveAll(this);
	return true;
}


bool UBaseBuildModel::StopTrace_Implementation(UObject* Instigator)
{
	bIsActivate = false;
	if (FrameActor)
	{
		FrameActor->Destroy();
	}
	UE_LOG(LogChamingCraftBuild, Display,
	       TEXT("[📦] UBaseBuildModel::StopTrace\n"));
	return true;
}

bool UBaseBuildModel::StartTrace_Implementation(UObject* Instigator)
{
	bIsActivate = true;
	UE_LOG(LogChamingCraftBuild, Display,
	       TEXT("[📦] UBaseBuildModel::StartTrace\n"));
	return true;
}
