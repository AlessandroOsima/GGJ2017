// Fill out your copyright notice in the Description page of Project Settings.

#include "KillerWave.h"
#include "LevelManager.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{

}

// Called every frame
void ALevelManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!CooldownOver)
	{
		TimeSinceLastActivation += DeltaTime;

		if (TimeSinceLastActivation >= CooldownTime)
		{
			CooldownOver = true;
			TimeSinceLastActivation = 0;
		}
	}
}

void ALevelManager::OnMIDIKeyPress(int Channel)
{
	if (!CooldownOver)
	{
		return;
	}

	for (FChannelMapping & mapping : ChannelMappings)
	{
		if (Channel >= mapping.RangeStart && Channel <= mapping.RangeEnd)
		{
			FString ActorName;
			
			if (mapping.ActorToActivate)
			{
				mapping.ActorToActivate->ActivatePulse();
				CooldownOver = false;
				break;
			}
		}
	}

	
}

