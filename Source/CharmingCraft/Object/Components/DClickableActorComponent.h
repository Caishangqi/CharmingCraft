/* Descrpeated Class because can only hanle mouse click events
 * from blueprint or in controller
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DClickableActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMouseClicked, UDClickableActorComponent*, ClickableActorComponent,
                                               UStaticMeshComponent*, StaticMeshRef, bool, isClicked);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHARMINGCRAFT_API UDClickableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDClickableActorComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "StaticMeshes")
	;
	UStaticMeshComponent* StaticMeshRef;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "boolean")
	;
	bool isClicked;

	UPROPERTY(BlueprintAssignable, Category= "Events")
	FOnMouseClicked onMouseClicked;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
