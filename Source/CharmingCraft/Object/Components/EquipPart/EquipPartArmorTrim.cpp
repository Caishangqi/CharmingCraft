// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartArmorTrim.h"

#include "../Core/CharmingCraftInstance.h"
#include "CharmingCraft/Object/Structs/FDArmorMaterial.h"

UEquipPartArmorTrim::UEquipPartArmorTrim()
{
	TypeSuffix = "Armor Trim";
	TypeSuffixShort = "Trim";
	Description = "Armor Trim is Armor Trim so it should be Armor Trim or you can also call it Armor Trim";
	ItemNeedToForge = 3;
	MaterialSlotIndex = 2;
}


void UEquipPartArmorTrim::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
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
	PartMaterial = FoundRow->TrimTexture;
}

void UEquipPartArmorTrim::OnRegister()
{
	Super::OnRegister();
}

void UEquipPartArmorTrim::BeginPlay()
{
	Super::BeginPlay();
	UEquipPartArmorTrim::UpdateRenderMesh(ComponentMaterial);
}
