// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Object/Enum/MaterialType.h"
#include "CharmingCraft/Object/Structs/FDMaterial.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "EquipPartComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UEquipPartComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipPartComponent();

	/* 属性 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Component Properties")
	EMaterial ComponentMaterial; //锻造这个部件所用的材料

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Component Properties")
	FDMaterial MaterialData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	int32 ItemNeedToForge; // 多少个材料才能锻造这个部件

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Component Properties")
	FString Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Component Properties")
	UDataTable* ComponentMaterialDataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		Category= "Naming")
	FString TypeSuffix;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		Category= "Naming")
	FString TypeSuffixShort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,
		Category= "Description")
	FString Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Graphic")
	TObjectPtr<UTexture2D> PartIcon; //这个部件在锻造GUI中的图标
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Graphic")
	int32 MaterialSlotIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Equip Part Render")
	UMaterial* PartMaterial; // Default Value
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Equip Part Mesh")
	UStaticMesh* PartMesh; // For Weapon

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	virtual void OnRegister() override;

	// 构造的时候依照玩家选择的 Material 调用数据表格的材料进行材质更替
	virtual void UpdateRenderMesh(EMaterial& NewComponentMaterialText);
};
