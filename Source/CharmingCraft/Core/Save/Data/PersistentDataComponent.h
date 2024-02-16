// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharmingCraft/Core/Save/Interface/ISerializable.h"
#include "Components/ActorComponent.h"
#include "PersistentDataComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UPersistentDataComponent : public UActorComponent, public ISerializable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPersistentDataComponent();

	// Native C++ Serialization
	virtual TSharedPtr<FJsonObject> SerializeToJson();

	/*!
	 * import JsonObject and modify UActorComponent internal Data, and return the modified
	 * ActorComponent address
	 * @param JsonObject UActorComponent internal Data need load
	 * @return Modified UActorComponent
	 */
	virtual UObject* LoadDataFromJson(TSharedPtr<FJsonObject> JsonObject)
	{
		return this;
	}

	// Unreal BluePrint Serialization Interface Implementation
	virtual UObject* Deserialize_Implementation(const FString& SerializeData) override;
	virtual FString Serialize_Implementation() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
