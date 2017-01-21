// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "KillerWave.h"
#include "KillerWaveGameMode.h"
#include "KillerWavePlayerController.h"
#include "KillerWaveCharacter.h"

AKillerWaveGameMode::AKillerWaveGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AKillerWavePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}