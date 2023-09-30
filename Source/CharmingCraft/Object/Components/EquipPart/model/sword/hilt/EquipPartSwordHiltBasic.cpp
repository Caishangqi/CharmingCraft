// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartSwordHiltBasic.h"

#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipPartSwordHiltBasic::UEquipPartSwordHiltBasic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TypeSuffix = "hilt";
	TypeSuffixShort = "Hilt";
	Description = "Hilt is Hilt so it should be Hilt or you can also call it Hilt";
	ItemNeedToForge = 1;
	MaterialSlotIndex = 1;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PartMeshFinder(
		TEXT(
			"StaticMesh'/Game/CharmingCraft/Assets/models/sword/hilt/hilt_default.hilt_default'"));
	if (PartMeshFinder.Succeeded())
	{
		PartMesh = PartMeshFinder.Object;
	}
}


// Called when the game starts
void UEquipPartSwordHiltBasic::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipPartSwordHiltBasic::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipPartSwordHiltBasic::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		ComponentMaterialDataTable = GameInstance->HiltBasicMaterial;
		if (ComponentMaterialDataTable)
		{
			TArray<FName> RowNames = ComponentMaterialDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FHiltBasicMaterial* CurrentRow = ComponentMaterialDataTable->FindRow<FHiltBasicMaterial>(
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
