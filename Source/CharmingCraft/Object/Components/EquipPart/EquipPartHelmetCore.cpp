// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartHelmetCore.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"

UEquipPartHelmetCore::UEquipPartHelmetCore()
{
	TypeSuffix = "Helmet Core";
	TypeSuffixShort = "Core";
	Description = "Helmet Core is Helmet Core so it should be Helmet Core or you can also call it Helmet Core";
	ItemNeedToForge = 2;
	MaterialSlotIndex = 0;
}

void UEquipPartHelmetCore::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		ComponentMaterialDataTable = GameInstance->ArmorMaterialDataTable;
		if (ComponentMaterialDataTable)
		{
			TArray<FName> RowNames = ComponentMaterialDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FDArmorMaterial* CurrentRow = ComponentMaterialDataTable->FindRow<FDArmorMaterial>(
					RowName, TEXT("UpdateRenderMesh"), true);

				if (CurrentRow && CurrentRow->Material == NewComponentMaterialText)
				{
					FoundRow = CurrentRow;
					UE_LOG(LogTemp, Error, TEXT("ROW FOUND!"));
					break;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("DataTable not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found!"));
	}
	PartMaterial = FoundRow->CoreTexture;
}

void UEquipPartHelmetCore::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartHelmetCore::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartHelmetCore::UpdateRenderMesh(ComponentMaterial);
}
