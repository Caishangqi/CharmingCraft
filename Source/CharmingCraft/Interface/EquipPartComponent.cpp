// Fill out your copyright notice in the Description page of Project Settings.
#include "EquipPartComponent.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipPartComponent::UEquipPartComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	/* 初始化 */
	ItemNeedToForge = 0;
	ComponentMaterial = EMaterial::AIR;
}


// Called when the game starts
void UEquipPartComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UEquipPartComponent::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance && !IsValid(ComponentMaterialDataTable))
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
}


// Called every frame
void UEquipPartComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipPartComponent::OnRegister()
{
	Super::OnRegister();
}
