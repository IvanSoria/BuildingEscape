// Ivan Soria 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//setup physics component
	void FindPhysicsComponent();

	//setup assumed input component
	void FindInputComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY(EditAnywhere)
	float Reach = 100.0;

	UPhysicsHandleComponent* PhysiscsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//raycast and grab what is in reach 
	void Grab();
	void Release();

	//return hit for first physics body in reach 
	const FHitResult GetFirstPhysicsBodyInReach();

	//returns start od reach line
	FVector GetReachLineStart();

	//returns current end of reach libe
	FVector GetReachLineEnd();
};
