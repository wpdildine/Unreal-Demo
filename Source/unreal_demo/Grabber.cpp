// My CopyWrite

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
	FindPhysicsHandleComponent();
	FindInputComponent();
	
}

void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("missing physics handle component %s"), *GetOwner()->GetName());
	}

}


void UGrabber::FindInputComponent() {

		InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found Input component %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetLineTraceStart(), GetLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *Hit.ToString());
	
	return Hit;

}

void UGrabber::Grab() {

	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed %s"), *GetOwner()->GetName());
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	if (ComponentToGrab) {
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}


}


void UGrabber::Released() {

	UE_LOG(LogTemp, Warning, TEXT("Grab Released %s"), *GetOwner()->GetName());
	PhysicsHandle->ReleaseComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}

}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return (PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach);

}
FVector UGrabber::GetLineTraceStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0.5), false, 0.0f, 0.0f, 20.0f);
	return PlayerViewPointLocation;

}

