// Fill out your copyright notice in the Description page of Project Settings.


#include "Seeds.h"

#include "CharmingCraft/Core/Builds/Module/BuildModuleManager.h"
#include "CharmingCraft/Core/Builds/Module/Modules/SeedsBuildModel.h"
#include "../Core/CharmingCraftInstance.h"

void USeeds::OnItemInteract(UItemStack* InteractItemStack, APawn* Instigator)
{
	Super::OnItemInteract(InteractItemStack, Instigator);

	UBuildModuleManager* BuildModuleManager = Cast<UCharmingCraftInstance>(Instigator->GetWorld()->GetGameInstance())->
		BuildModuleManager;
	BuildModuleManager->StartCustomModel(Instigator, BuildModel);
	USeedsBuildModel* SeedBuildModel = Cast<USeedsBuildModel>(
		BuildModuleManager->CurrentLoadedBuildModels.Find(BuildModel.GetDefaultObject()->BuildModelName)->Get());
	SeedBuildModel->ModelCachedItemStack = InteractItemStack;
}
