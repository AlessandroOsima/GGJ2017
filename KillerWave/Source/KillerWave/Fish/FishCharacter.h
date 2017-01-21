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

	UFUNCTION(BlueprintCallable, Category = "FishCharacter")
	void SetMoveDestination(const FVector DestLocation, int waveSignal);
	UFUNCTION(BlueprintCallable, Category = "FishCharacter")
	void IlluminateFish(bool Illuminate);
	UFUNCTION(BlueprintNativeEvent, Category = "FishCharacter")
	void OnIlluminate();
	UFUNCTION(BlueprintNativeEvent, Category = "FishCharacter")
	void OnDeluminate();

protected:
	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;

private:
	void MoveUpdate(float DeltaTime);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
		float MoveSpeed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
		float RotateSpeed = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
		float AccelerationFactor = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	bool SinusoidalSwim;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float SinusoidalAmplitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	FVector CurrentDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	float DistanceToStop;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	float SinSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	float MinSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	float CurrentSin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FishCharacter")
	float CurrentSpeed;
protected:
	/** Type of signal received.*/
	int32 waveSignalReceived;

	//Movement Parameters
	FVector bDestination;
	FVector bDirection;
	FVector bCurrentForward;
	float bDistance;
	//Sinusoidal Parameters
	int bSinDirection;
};


