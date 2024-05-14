// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartSwordFullerReinforced.h"

#include "../Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipPartSwordFullerReinforced::UEquipPartSwordFullerReinforced()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TypeSuffix = "reinforced fuller";
	TypeSuffixShort = "Fuller";
	Description =
		"reinforced fuller is reinforced fuller so it should be reinforced fuller or you can also call it reinforced fuller";
	ItemNeedToForge = 2;
	MaterialSlotIndex = 1;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PartMeshFinder(
		TEXT(
			"StaticMesh'/Game/CharmingCraft/Assets/models/sword/fuller/reinforced_fuller/reinforced_fuller_default.reinforced_fuller_default'"));
	if (PartMeshFinder.Succeeded())
	{
		PartMesh = PartMeshFinder.Object;
	}
}


// Called when the game starts
void UEquipPartSwordFullerReinforced::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipPartSwordFullerReinforced::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipPartSwordFullerReinforced::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		ComponentMaterialDataTable = GameInstance->FullerReinforcedMaterial;
		if (ComponentMaterialDataTable)
		{
			TArray<FName> RowNames = ComponentMaterialDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FFullerReinforcedMaterial* CurrentRow = ComponentMaterialDataTable->FindRow<FFullerReinforcedMaterial>(
					RowName, TEXT("UpdateRenderMesh"), true);

				if (CurrentRow && CurrentRow->Material == NewComponentMaterialText)
				{
					MaterialProperties = CurrentRow;
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
