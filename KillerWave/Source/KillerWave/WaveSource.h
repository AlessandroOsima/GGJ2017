// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WaveSource.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class FExpansionDirection : uint8
{
	Expanding,
	Still,
	Reducing
};

UCLASS()
class KILLERWAVE_API AWaveSource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSource();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UFUNCTION(BlueprintNativeEvent, Category = "WaveSource")
	void ActivatePulse();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "WaveSource")
	USphereComponent * SphereCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveSource")
	float MaxRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveSource")
	float ExpansionDelta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveSource")
	float ReductionDelta;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WaveSource")
	float StillTimeDuration;

	UPROPERTY(BlueprintReadOnly, Category = "WaveSource")
	bool StartingPulse = false;

	UPROPERTY(BlueprintReadOnly, Category = "WaveSource")
	float StillTime = 0;

	float ExpandTime = 0;

	UPROPERTY(BlueprintReadOnly, Category = "WaveSource")
	FExpansionDirection Direction = FExpansionDirection::Expanding;

	UPROPERTY(BlueprintReadOnly, Category = "WaveSource")
	float OriginalRadius = 0;
};
