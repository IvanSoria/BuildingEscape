// Ivan Soria 2017

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"))
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT CameraPosition, OUT CameraRotation);

	UE_LOG(LogTemp, Warning, TEXT("Camera position at %s and rotation at %s"), *CameraPosition.ToString(), *CameraRotation.ToString())
		// Get player viewpoint this tick 

		/*if (GetOwner()->ActorLineTraceSingle(

		))*/

	FVector LineStart = CameraPosition;
	FVector LineEnd = CameraPosition + CameraRotation.Vector()*Reach;

	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false, -1.0, 0.0, 12.333);


	//draw a line in his current view point

	//log what i see

}

