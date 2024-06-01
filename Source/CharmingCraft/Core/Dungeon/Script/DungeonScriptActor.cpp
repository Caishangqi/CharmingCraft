// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonScriptActor.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"


// Sets default values
ADungeonScriptActor::ADungeonScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	VolumeBoxComponent = CreateDefaultSubobject<UBoxComponent>("VolumeBoxComponent");
	VolumeBoxComponent->SetupAttachment(RootComponent);
	if (bEnableVolumeTriggerEvent == true)
	{
		VolumeBoxComponent->SetGenerateOverlapEvents(true);
	}
	else
	{
		VolumeBoxComponent->SetGenerateOverlapEvents(false);
	}
}

void ADungeonScriptActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (bEnableInteractEvent && OnInteractScript)
	{
		TObjectPtr<UNativeScriptObject> ScriptObject = OnInteractScript.GetDefaultObject();
		ScriptObject->ParentScriptActor = this;
		RunningScriptObjectInstance.Add(ScriptObject);
		ScriptObject->StartScript(InstigatorPawn);
	}
}

bool ADungeonScriptActor::AddRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject)
{
	if (!RunningScriptObjectInstance.Contains(ScriptObject))
	{
		RunningScriptObjectInstance.Add(ScriptObject);
		ScriptObject->ScriptState = EScriptState::Ready;
		return true;
	}
	return false;
}


bool ADungeonScriptActor::RemoveRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject)
{
	if (RunningScriptObjectInstance.Contains(ScriptObject))
	{
		ScriptObject->ScriptState = EScriptState::Remove;
		RunningScriptObjectInstance.Remove(ScriptObject);
		return true;
	}
	return false;
}

bool ADungeonScriptActor::SuspendRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject)
{
	if (RunningScriptObjectInstance.Contains(ScriptObject))
	{
		ScriptObject->ScriptState = EScriptState::Suspend;
	}
	return false;
}

bool ADungeonScriptActor::FilterBySubClass(TArray<UClass*> ContainerClasses, UObject* TargetObject)
{
	for (auto Element : ContainerClasses)
	{
		if (TargetObject->IsA(Element))
		{
			return true;
		}
	}
	return false;
}


void ADungeonScriptActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (bEnableVolumeTriggerEvent && OnOverlapScript)
	{
		if (FilterBySubClass(WhiteListTriggerClass, OtherActor) && !FilterBySubClass(BlackListTriggerClass, OtherActor))
		{
			TObjectPtr<UNativeScriptObject> ScriptObject = OnOverlapScript.GetDefaultObject();
			ScriptObject->ParentScriptActor = this;
			if (OtherActor->IsA(ACharacter::StaticClass()))
			{
				RunningScriptObjectInstance.Add(ScriptObject);
				ScriptObject->StartScript(OtherActor);
			}
		}
	}
}

// Called when the game starts or when spawned
void ADungeonScriptActor::BeginPlay()
{
	Super::BeginPlay();
	if (bEnableVolumeTriggerEvent)
	{
		VolumeBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADungeonScriptActor::OnOverlapBegin);
	}
	if (!bEnableScriptActorTickScript)
	{
		SetActorTickEnabled(false);
	}
}

// Called every frame
void ADungeonScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bEnableScriptActorTickScript)
	{
		for (TObjectPtr<UNativeScriptObject> ScriptObjectInstance : RunningScriptObjectInstance)
		{
			if (ScriptObjectInstance->ScriptState != EScriptState::Suspend && !ScriptObjectInstance->bEnableScriptTick)
			{
				ScriptObjectInstance->OnScriptTick(ScriptObjectInstance->Instigator);
			}
			if (ScriptObjectInstance->ScriptState == EScriptState::Remove)
			{
				RemoveRunningScriptObject(ScriptObjectInstance);
			}
		}
	}
}
