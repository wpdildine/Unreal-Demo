// My CopyWrite

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
	///Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	Controller = GetOwner()->FindComponentByClass<UInputComponent>();
	
	// ...
	if(PhysicsHandle){}
	else {
		UE_LOG(LogTemp, Error, TEXT("missing physics handle component %s"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0.5),
		false,
		0.0f,
		0.0f,
		20.0f
	);

	FHitResult Hit;
	
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParams);

	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *Hit.ToString() );
	UE_LOG(LogTemp, Warning, TEXT("I AM Here %s and %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

}

