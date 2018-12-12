// Fill out your copyright notice in the Description page of Project Settings.
#include "PositionReport.h"
#include <string>
#include "GameFramework/Actor.h"
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
	FString _name = GetOwner()->GetName();
	FFloat16 _positionX = GetOwner()->GetActorLocation().X;
	FString _objPosition = FString::SanitizeFloat(_positionX);

	UE_LOG(LogTemp, Warning, TEXT("Your message %s and is at x position %s"), *_name, *_objPosition);
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}

