// Fill out your copyright notice in the Description page of Project Settings.

#include "KillerWave.h"
#include "WaveSource.h"


// Sets default values
AWaveSource::AWaveSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
}

// Called when the game starts or when spawned
void AWaveSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveSource::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (StartingPulse)
	{

		float UnsclaedSphereRadiusMod = 0;

		switch (Direction)
		{
		case FExpansionDirection::Expanding :
		{
			UnsclaedSphereRadiusMod = SphereCollision->GetUnscaledSphereRadius() + (ExpansionDelta * DeltaTime * 1);
			break;
		}

		case FExpansionDirection::Still:
		{
			UnsclaedSphereRadiusMod = SphereCollision->GetUnscaledSphereRadius();
			StillTime += DeltaTime;
			break;
		}

		case FExpansionDirection::Reducing:
		{
			UnsclaedSphereRadiusMod = SphereCollision->GetUnscaledSphereRadius() + (ReductionDelta * DeltaTime * -1);
			break;
		}

		default:
			break;
		}

		if (Direction == FExpansionDirection::Expanding && UnsclaedSphereRadiusMod >= MaxRadius)
		{
			UnsclaedSphereRadiusMod = MaxRadius;
			Direction = FExpansionDirection::Still;
		}

		if (Direction == FExpansionDirection::Still && StillTime >= StillTimeDuration)
		{
			StillTime = 0;
			Direction = FExpansionDirection::Reducing;
		}
		
		if(Direction == FExpansionDirection::Reducing && UnsclaedSphereRadiusMod <= OriginalRadius)
		{
			UnsclaedSphereRadiusMod = OriginalRadius;
			StartingPulse = false;
		}

		SphereCollision->SetSphereRadius(UnsclaedSphereRadiusMod);
	}
}

void AWaveSource::ActivatePulse_Implementation()
{
	if (!StartingPulse)
	{
		StartingPulse = true;
		Direction = FExpansionDirection::Expanding;
		OriginalRadius = SphereCollision->GetUnscaledSphereRadius();
	}
}


