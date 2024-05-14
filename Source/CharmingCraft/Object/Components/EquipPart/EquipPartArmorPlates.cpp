// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorPlates.h"

#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"


UEquipPartArmorPlates::UEquipPartArmorPlates()
{
	TypeSuffix = "Armor Plates";
	TypeSuffixShort = "Plates";
	Description = "Armor Plates is Armor Plates so it should be Armor Plates or you can also call it Armor Plates";
	ItemNeedToForge = 4;
	MaterialSlotIndex = 1;
}

void UEquipPartArmorPlates::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
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
	PartMaterial = FoundRow->PlateTexture;
}

void UEquipPartArmorPlates::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartArmorPlates::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartArmorPlates::UpdateRenderMesh(ComponentMaterial);
}
