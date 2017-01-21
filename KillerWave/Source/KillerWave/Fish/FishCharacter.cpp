// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "KillerWave.h"
#include "FishCharacter.h"

AFishCharacter::AFishCharacter()
{
	CurrentSin = 0;
	bSinDirection = 1;
	PrimaryActorTick.bCanEverTick = true;
	CurrentSpeed = MoveSpeed;
}

void AFishCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveUpdate(DeltaTime);
}

void AFishCharacter::SetMoveDestination(const FVector DestLocation, int waveSignal)
{
	if (DestLocation != bDestination || waveSignalReceived != waveSignal)
	{
		bDestination = DestLocation;
		waveSignalReceived = waveSignal;
		CurrentSpeed = MoveSpeed;
		//bCurrentForward = GetActorForwardVector();
		bDistance = FVector::Dist(bDestination, GetActorLocation());
		if (waveSignalReceived == 1)
		{
			bDirection = bDestination - GetActorLocation();
		}
		else if (waveSignalReceived == -1)
		{
			bDirection = GetActorLocation() - bDestination;
		}
		bDirection.Normalize();
	}
}
void AFishCharacter::MoveUpdate(float DeltaTime)
{
	bDistance = FVector::Dist(bDestination, GetActorLocation());

	bCurrentForward = FMath::Lerp(bCurrentForward, bDirection, RotateSpeed);
	bCurrentForward.Z = 0;
	bCurrentForward.Normalize();

	CurrentDirection = bCurrentForward;

	if (SinusoidalSwim)
	{
		CurrentSin = CurrentSin + bSinDirection*DeltaTime*SinSpeed;
		if (CurrentSin >= 1)
		{
			bSinDirection = -1;
		}
		else if(CurrentSin <= -1)
		{
			bSinDirection = 1;
		}
		FVector Right = FVector(CurrentDirection.Y, -CurrentDirection.X, CurrentDirection.Z);
		Right = Right*CurrentSin*SinusoidalAmplitude;

		CurrentDirection = CurrentDirection + Right;
		CurrentDirection.Normalize();
	}

	SetActorRotation(CurrentDirection.Rotation());

	if (CurrentSpeed > MinSpeed)
	{
		CurrentSpeed = CurrentSpeed - MoveSpeed*(1 - AccelerationFactor)*DeltaTime;
	}	
	if (bDistance < DistanceToStop)
	{
		CurrentSpeed = CurrentSpeed - MoveSpeed*DeltaTime;
	}
	FVector nextLocation = GetActorLocation() + GetActorForwardVector()*DeltaTime*CurrentSpeed;
	SetActorLocation(nextLocation);
}

void AFishCharacter::IlluminateFish(bool Illuminate)
{
	if (Illuminate)
	{
		OnIlluminate();
	}
	else
	{
		OnDeluminate();
	}
}

void AFishCharacter::Eat()
{
	OnEated();
}

void AFishCharacter::OnIlluminate_Implementation()
{
}

void AFishCharacter::OnDeluminate_Implementation()
{
}

void AFishCharacter::OnEated_Implementation()
{
}