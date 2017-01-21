// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "KillerWave.h"
#include "FishController.h"

AFishController::AFishController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AFishController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MoveUpdate(DeltaTime);
}

void AFishController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AFishController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AFishController::OnSetDestinationReleased);
}


void AFishController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetMoveDestination(Hit.ImpactPoint, 1);
	}
}


void AFishController::SetMoveDestination(const FVector DestLocation, int waveSignal)
{
	waveSignalReceived = waveSignal;

	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		bDirection = DestLocation - MyPawn->GetActorLocation();
		bDirection.Normalize();
		// We need to issue move command only if far enough in order for walk animation to play correctly
		//if (Distance > 120.0f)
		{
			waveSignalReceived = 1;
			bDestination = DestLocation;
		}
	}
}

void AFishController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	waveSignalReceived = 1;
}

void AFishController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	//waveSignalReceived = 0;
}

void AFishController::MoveUpdate(float DeltaTime)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		FVector nextLocation = MyPawn->GetActorLocation() + bDirection*DeltaTime*MoveSpeed;
		MyPawn->SetActorLocation(nextLocation);
	}
}