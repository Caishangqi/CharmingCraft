// Fill out your copyright notice in the Description page of Project Settings.


#include "PersistentDataComponent.h"

#include "CharmingCraft/Core/Save/Lib/SerializationLib.h"
#include "CharmingCraft/Object/Class/Core/CharmingCraftInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPersistentDataComponent::UPersistentDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TSharedPtr<FJsonObject> UPersistentDataComponent::SerializeToJson()
{
	CREATE_JSON_OBJECT(SerilizeJson);
	return SerilizeJson;
}

UObject* UPersistentDataComponent::Deserialize_Implementation(const FString& SerializeData)
{
	CREATE_JSON_OBJECT_FROM_STRING(DeserializeReader, DeserializeJsonObject, SerializeData);
	return LoadDataFromJson(DeserializeJsonObject);
}

FString UPersistentDataComponent::Serialize_Implementation()
{
	EXPORT_JSON_OBJECT_AND_SERIALIZE(SerializeToJson(), SerilizeString)
	return SerilizeString;
}


// Called when the game starts
void UPersistentDataComponent::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// ...
}


// Called every frame
void UPersistentDataComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
