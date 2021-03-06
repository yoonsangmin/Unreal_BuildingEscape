// Copyright Michael Bridges 2019

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFrameWork/Actor.h"

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressureplate set!"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);

		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float &DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	// CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.f);
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float &DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	// CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.f);
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}