// Ivan Soria 2017

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find the Door
	Owner = GetOwner();

	//Finds the player pawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (GetMassOfActors() >= 50)
	{
		//Set the door roation
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	
	//check if it is time to close that door 
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCLoseDelay)
	{
		CloseDoor();
	}

}

float UOpenDoor::GetMassOfActors()
{
    TArray<AActor*> ActorsThatOpen;
    float TotalMass = 0.0;
    
    PressurePlate->GetOverlappingActors(ActorsThatOpen);
    
    for( AActor* Actor : ActorsThatOpen)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    
    return TotalMass;
    
    
}

void UOpenDoor::OpenDoor()
{
	FRotator NewRotator = FRotator(0, OpenAngle, 0);
	Owner->SetActorRotation(NewRotator);
	
}

void UOpenDoor::CloseDoor()
{
	FRotator NewRotator = FRotator(0, CloseAngle, 0);
	Owner->SetActorRotation(NewRotator);

}
