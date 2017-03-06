// Ivan Soria 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	AActor *Owner;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 60.0;

	UPROPERTY(EditAnywhere)
	float CloseAngle = 0.0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	
	AActor *ActorThatOpens; //Remember pawn inherits from actor 

	FRotator OpenRotator = FRotator(0,OpenAngle,0);
	FRotator CloseRotator = FRotator(0, CloseAngle, 0);

	
};
