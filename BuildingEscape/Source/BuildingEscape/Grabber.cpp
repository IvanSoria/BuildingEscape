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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComponent();
	FindInputComponent();
}

///look for physics handle after game has started 
void UGrabber::FindPhysicsComponent()
{
	PhysiscsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysiscsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle component not found in Actor: %s"), *GetOwner()->GetName())
	}
}
///look for Inout component after game has started 
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///Bid the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component not found in Actor: %s"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	//Line trace and see if we reach any actors with physics body collision channel set 
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
	AActor* ActorHit = Hit.GetActor();
	///if we hit something then attach a pysics handle 
	if (ActorHit) {
		//TODO: attach physics handle 
		PhysiscsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	//Release physics handle
	PhysiscsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LineEnd = GetReachLineEnd();

	if (PhysiscsHandle->GrabbedComponent)
	{
		PhysiscsHandle->SetTargetLocation(LineEnd);
	}
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector LineStart = GetReachLineStart();
	FVector LineEnd = GetReachLineEnd();
	//Line-Trace (AKA ray-cast) out to reach a distance
	FHitResult Hit;
	///setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		LineStart,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return Hit;
}
FVector UGrabber::GetReachLineEnd()
{
	FVector CameraPosition;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT CameraPosition, OUT CameraRotation);
	///draw a line in his current view point
	return CameraPosition + CameraRotation.Vector()*Reach;
}

FVector UGrabber::GetReachLineStart()
{
	FVector CameraPosition;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT CameraPosition, OUT CameraRotation);
	return CameraPosition;
}