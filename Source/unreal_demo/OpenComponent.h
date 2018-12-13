// My CopyWrite

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_DEMO_API UOpenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenComponent();
private:


	UPROPERTY(EditAnywhere)
		float OpenAngle = 180.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* _pressurePlate;

	AActor* ActorThatOpens;
	AActor* Owner;
		

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5f;

	float LastDoorOpenTime;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
