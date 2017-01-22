// Fill out your copyright notice in the Description page of Project Settings.

#include "KillerWave.h"
#include "WaveSource.h"


// Sets default values
AWaveSource::AWaveSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RadarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadarMesh"));

	SetRootComponent(SphereCollision);
	RadarMesh->AttachToComponent(SphereCollision, FAttachmentTransformRules::KeepRelativeTransform);
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
			float ScaleDelta = (ExpansionDelta * DeltaTime * ScaleDeltaMultiplier) * 1;
			FVector CurrentScale = RadarMesh->GetComponentScale();
			RadarMesh->SetWorldScale3D(FVector(CurrentScale.X + ScaleDelta, CurrentScale.Y + ScaleDelta, CurrentScale.Z));
			ExpandTime += DeltaTime;
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
			float ScaleDelta = (ExpansionDelta * DeltaTime * ScaleDeltaMultiplier) * -1;
			FVector CurrentScale = RadarMesh->GetComponentScale();
			RadarMesh->SetWorldScale3D(FVector(CurrentScale.X + ScaleDelta, CurrentScale.Y + ScaleDelta, CurrentScale.Z));
			break;
		}

		default:
			break;
		}

		if (Direction == FExpansionDirection::Expanding && UnsclaedSphereRadiusMod >= MaxRadius)
		{
			UnsclaedSphereRadiusMod = MaxRadius;
			UE_LOG(LogTemp, Log, TEXT("Expansion Time %f"), ExpandTime)
			Direction = FExpansionDirection::Still;
			WaveSent();
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
			OnPulseEnd();
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
		ExpandTime = 0;
	}
}


void AWaveSource::WaveSent_Implementation()
{
}


