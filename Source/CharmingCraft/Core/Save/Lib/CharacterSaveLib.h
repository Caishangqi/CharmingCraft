// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "CharmingCraft/Core/Save/Data/FInternalCostume.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterSaveLib.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "CharacterSaveLibarary"))
class CHARMINGCRAFT_API UCharacterSaveLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Render")
	static void ApplyPreviewCostumeToPlayer(ASkeletalMeshActor* SkeletalMeshActor, UMaterial* PreviewMaterial)
	{
		USkeletalMeshComponent* MeshComp = SkeletalMeshActor->GetSkeletalMeshComponent();
		MeshComp->SetMaterial(0, PreviewMaterial);
	}

	// TODO: research some Predicate
	UFUNCTION(BlueprintCallable, Category = "Render")
	static UMaterial* FindPreviewMaterialFromCostumeId(UDataTable* DataTable, int32 CostumeId)
	{
		if (DataTable != nullptr)
		{
			FInternalCostume FoundCostume;
			DataTable->ForeachRow<FInternalCostume>(
				TEXT("AnyContextString"), [&](const FName& Key, const FInternalCostume& Costume)
				{
					if (Costume.id == CostumeId)
					{
						FoundCostume = Costume;
					}
				});

			// 这里你已经找到了匹配的CostumeMaterial
			TObjectPtr<UMaterial> FoundMaterial = FoundCostume.CostumeMaterial;
			return FoundMaterial;
		}
		else
		{
			return nullptr;
		}
	}
};
