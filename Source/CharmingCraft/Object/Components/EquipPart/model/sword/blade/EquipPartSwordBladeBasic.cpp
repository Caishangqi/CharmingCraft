// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipPartSwordBladeBasic.h"

#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"


// Sets default values for this component's properties
UEquipPartSwordBladeBasic::UEquipPartSwordBladeBasic()
{
	UE_LOG(LogTemp, Warning, TEXT("(!) UEquipPartSwordBladeBasic::UEquipPartSwordBladeBasic() -0"))
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TypeSuffix = "blade";
	TypeSuffixShort = "Blade";
	Description = "Blade is Blade so it should be Blade or you can also call it Blade";
	ItemNeedToForge = 2;
	MaterialSlotIndex = 1;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PartMeshFinder(
		TEXT(
			"StaticMesh'/Game/CharmingCraft/Assets/models/sword/blade/basic/basic_metal_blade.basic_metal_blade'"));
	if (PartMeshFinder.Succeeded())
	{
		PartMesh = PartMeshFinder.Object;
	}
	UE_LOG(LogTemp, Warning, TEXT("(!) UEquipPartSwordBladeBasic::UEquipPartSwordBladeBasic() -1"))
}


// Called when the game starts
void UEquipPartSwordBladeBasic::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEquipPartSwordBladeBasic::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipPartSwordBladeBasic::UpdateRenderMesh(EMaterial& NewComponentMaterialText)
{
	Super::UpdateRenderMesh(NewComponentMaterialText);
	UCharmingCraftInstance* GameInstance = Cast<UCharmingCraftInstance>(
		GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		ComponentMaterialDataTable = GameInstance->BladeBasicMaterial;
		if (ComponentMaterialDataTable)
		{
			TArray<FName> RowNames = ComponentMaterialDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FBladeBasicMaterial* CurrentRow = ComponentMaterialDataTable->FindRow<FBladeBasicMaterial>(
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
