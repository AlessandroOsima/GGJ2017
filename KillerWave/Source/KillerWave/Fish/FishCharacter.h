// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "FishCharacter.generated.h"

UCLASS()
class AFishCharacter : public AActor
{
	GENERATED_BODY()

public:
	AFishCharacter();

	UFUNCTION(BlueprintCallable, Category = "FishController")
	void SetMoveDestination(const FVector DestLocation, int waveSignal);

protected:
	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;

private:
	void MoveUpdate(float DeltaTime);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
		float MoveSpeed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
		float RotateSpeed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
		float AccelerationFactor = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController")
	bool SinusoidalSwim;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishController", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float SinusoidalAmplitude;

protected:
	/** Type of signal received.*/
	int32 waveSignalReceived; //T

	//Movement Parameters
	FVector bDestination;
	FVector bDirection;
	FVector bCurrentForward;
	float bDistance;
	float bCurrentSpeed;
	int bSinDirection;
	float bCurrentSin;


};


