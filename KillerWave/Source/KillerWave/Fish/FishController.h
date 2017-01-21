// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "FishController.generated.h"

UCLASS()
class AFishController : public APlayerController
{
	GENERATED_BODY()

public:
	AFishController();

	UFUNCTION(BlueprintCallable, Category = "FishController")
	void SetMoveDestination(const FVector DestLocation, int waveSignal);

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	/** Navigate Fish to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:
	void MoveUpdate(float DeltaTime);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
	float MoveSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
	float RotateSpeed;

protected:
	/** Type of signal received.*/
	int32 waveSignalReceived; //T

	//Movement Parameters
	FVector bDestination;
	FVector bDirection;

};


