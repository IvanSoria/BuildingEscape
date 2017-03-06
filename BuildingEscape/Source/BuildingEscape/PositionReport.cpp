// Ivan Soria 2017

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Actor = GetOwner();
	ObjectName = Actor->GetName();
	Transform = Actor->GetActorTransform();
	Postion = Transform.GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s is at X=%f Y=%f Z=%f"), *ObjectName, Postion.X, Postion.Y, Postion.Z)
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

