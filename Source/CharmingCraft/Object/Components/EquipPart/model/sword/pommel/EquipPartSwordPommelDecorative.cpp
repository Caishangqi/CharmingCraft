// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartSwordPommelDecorative.h"

#include "../Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipPartSwordPommelDecorative::UEquipPartSwordPommelDecorative()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TypeSuffix = "pommel";
	TypeSuffixShort = "Pommel";
	Description = "Pommel is Pommel so it should be Pommel or you can also call it Pommel";
	ItemNeedToForge = 1;
	MaterialSlotIndex = 1;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PartMeshFinder(
		TEXT(
			"StaticMesh'/Game/CharmingCraft/Assets/models/sword/pommel/pommel_default.pommel_default'"));
	if (PartMeshFinder.Succeeded())
	{
		PartMesh = PartMeshFinder.Object;
	}
}


// Called when the game starts
void UEquipPartSwordPommelDecorative::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipPartSwordPommelDecorative::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipPartSwordPommelDecorative::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		ComponentMaterialDataTable = GameInstance->PommelDecorativeMaterial;
		if (ComponentMaterialDataTable)
		{
			TArray<FName> RowNames = ComponentMaterialDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FPommelDecorativeMaterial* CurrentRow = ComponentMaterialDataTable->FindRow<FPommelDecorativeMaterial>(
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
