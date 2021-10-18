// Copyright Michael Bridges 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void OpenDoor(float &DeltaTime);
	void CloseDoor(float &DeltaTime);

private:
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnyWhere)
	float OpenAngle = 90.f;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnyWhere)
	float DoorCloseDelay = .5f;

	UPROPERTY(EditAnyWhere)
	float DoorOpenSpeed = 1.f;

	UPROPERTY(EditAnyWhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnyWhere)
	ATriggerVolume *PressurePlate = NULL;

	UPROPERTY(EditAnyWhere)
	AActor *ActorThatOpens = NULL;
};
