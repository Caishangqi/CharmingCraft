// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeScriptObject.h"
#include "CharmingCraft/Core/Dungeon/Interface/ScriptActorInterface.h"
#include "CharmingCraft/Core/Interact/NativeInteractActor.h"
#include "ScriptActor.generated.h"

class UBoxComponent;

/*!
 * ScriptActor is a special actor that contain custom script, the script can trigger
 * by 2 ways (currently) by overlap and interact, user could disable scripts when they
 * do not want use.
 */
UCLASS()
class CHARMINGCRAFT_API AScriptActor : public ANativeInteractActor, public IScriptActorInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnableInteractEvent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnableVolumeTriggerEvent;

	// Default is false because usually script should not tick
	// it more like a function
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnableScriptActorTickScript = false;

	// Alter the size of Box component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> VolumeBoxComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	// Enable filter to control what object could trigger the script
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEnableFilter = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Filter", meta=(EditCondition="bEnableFilter"))
	TArray<UClass*> WhiteListTriggerClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "Filter", meta=(EditCondition="bEnableFilter"))
	TArray<UClass*> BlackListTriggerClass;

	/*!
	 * The script will execute when the object "Interact" with the Script actor
	 * @see DGameplayInterface.h
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bEnableInteractEvent"))
	TSubclassOf<UNativeScriptObject> OnInteractScript;

	/*!
	 * The script will execute when the object "Overlap" with the Script actor BoxComponent
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bEnableVolumeTriggerEvent"))
	TSubclassOf<UNativeScriptObject> OnOverlapScript;

	// Should not modify through editor in runtime, debug only
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UNativeScriptObject>> RunningScriptObjectInstance;

public:
	// Sets default values for this actor's properties
	AScriptActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual bool AddRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject);

	virtual bool RemoveRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject);

	virtual bool SuspendRunningScriptObject_Implementation(UNativeScriptObject* ScriptObject);

	/*!
	 * Filter a abject through a array of Class, if the object is the subclass
	 * of any element in the array, then the object is pass the filter
	 * 
	 * @param ContainerClasses The Filter that made of array of classes
	 * @param TargetObject The Object that you want to pass in the filter
	 * @return whether the filter's object match the target object Classes
	 */
	UFUNCTION(BlueprintCallable)
	bool FilterBySubClass(TArray<UClass*> ContainerClasses, UObject* TargetObject);

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
