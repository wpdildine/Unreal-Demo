// My CopyWrite

#include "OpenComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenComponent::UOpenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenComponent::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();

	
	
	
}

void UOpenComponent::OpenDoor()
{

	Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
}

void UOpenComponent::CloseDoor()
{
	
	Owner->SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}


// Called every frame
void UOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_pressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		//UE_LOG(LogTemp, Warning, TEXT("Open"));
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
		//UE_LOG(LogTemp, Warning, TEXT("Close"));
	}
	//Opendoor will now be here.

	// ...
}

