// My CopyWrite

#include "OpenComponent.h"
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
	
	
}

void UOpenComponent::OpenDoor()
{
	AActor *_actor = GetOwner();
	FRotator _nRotation = FRotator(0.0f, 180.0f, 0.0f);
	_actor->SetActorRotation(_nRotation);
}


// Called every frame
void UOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_pressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	//Opendoor will now be here.

	// ...
}

