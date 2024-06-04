// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Dungeon/Data/NativeBaseDungeonInstance.h"
#include "CharmingCraft/Core/Dungeon/Script/Base/ScriptActor.h"
#include "NativeDungeonEntrance.generated.h"

UCLASS()
class CHARMINGCRAFT_API ANativeDungeonEntrance : public AScriptActor
{
	GENERATED_BODY()

public:
	// The Dungeon that the entrace will travel player to
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ANativeBaseDungeonInstance> DungeonInstanceClass;
	// The Name of the Entrance
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DungeonEntraceName;

public:
	// Sets default values for this actor's properties
	ANativeDungeonEntrance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
