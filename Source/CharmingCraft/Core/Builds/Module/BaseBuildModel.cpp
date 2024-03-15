// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuildModel.h"

#include "BuildModuleManager.h"
#include "CharmingCraft/Core/Log/Logging.h"

UBaseBuildModel::UBaseBuildModel()
{
	BuildModuleManager = Cast<UBuildModuleManager>(GetOuter());
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


bool UBaseBuildModel::StopTrace_Implementation(UObject* Instigator)
{
	bIsActivate = false;
	UE_LOG(LogChamingCraftCraftBuild, Display,
	       TEXT("[📦] UBaseBuildModel::StopTrace\n"));
	return true;
}

bool UBaseBuildModel::StartTrace_Implementation(UObject* Instigator)
{
	bIsActivate = true;
	UE_LOG(LogChamingCraftCraftBuild, Display,
	       TEXT("[📦] UBaseBuildModel::StartTrace\n"));
	return true;
}
