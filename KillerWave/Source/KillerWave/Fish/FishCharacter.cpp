// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "KillerWave.h"
#include "FishCharacter.h"

AFishCharacter::AFishCharacter()
{
	bCurrentSin = 0;
	bSinDirection = 1;
	PrimaryActorTick.bCanEverTick = true;
}

void AFishCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (waveSignalReceived == 1)
	{
		MoveUpdate(DeltaTime);
	}	
}

void AFishCharacter::SetMoveDestination(const FVector DestLocation, int waveSignal)
{
	if (DestLocation != bDestination || waveSignalReceived != waveSignal)
	{
		bDestination = DestLocation;
		waveSignalReceived = waveSignal;
		bCurrentSpeed = MoveSpeed;
		bCurrentForward = GetActorForwardVector();
		bDistance = FVector::Dist(bDestination, GetActorLocation());

		bDirection = bDestination - GetActorLocation();
		bDirection.Normalize();
	}
}
void AFishCharacter::MoveUpdate(float DeltaTime)
{
	bCurrentForward = (bCurrentForward / RotateSpeed + bDirection);
	bCurrentForward.Normalize();

	CurrentDirection = bCurrentForward;

	if (SinusoidalSwim)
	{
		bCurrentSin = bCurrentSin + bSinDirection*DeltaTime*bCurrentSpeed;
		if (bCurrentSin >= 1 || bCurrentSin <= -1)
		{
			bSinDirection = bSinDirection*-1;
		}
		FVector Right = FVector(bCurrentForward.Y, -bCurrentForward.X, bCurrentForward.Z);
		Right = Right*bCurrentSin*SinusoidalAmplitude;

		CurrentDirection += Right;
		CurrentDirection.Normalize();
	}

	SetActorRotation(CurrentDirection.Rotation());

	bCurrentSpeed = bCurrentSpeed - MoveSpeed*(1 - AccelerationFactor);
	FVector nextLocation = GetActorLocation() + GetActorForwardVector()*DeltaTime*bCurrentSpeed;
	SetActorLocation(nextLocation);
}