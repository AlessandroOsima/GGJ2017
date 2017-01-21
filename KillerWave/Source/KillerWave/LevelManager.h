// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WaveSource.h"
#include "LevelManager.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FChannelMapping
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="ChannelMapping")
	AWaveSource * ActorToActivate;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ChannelMapping")
	int RangeStart = 0;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "ChannelMapping")
	int RangeEnd = 0;
};

UCLASS()
class KILLERWAVE_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Level Manager")
	void OnMIDIKeyPress(int Channel);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level Manager")
	int MIDIDeviceToUse = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level Manager")
	bool LogMIDIDevices = 0;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Level Manager")
	TArray<FChannelMapping> ChannelMappings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level Manager")
	float CooldownTime = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Level Manager")
	float TimeSinceLastActivation = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Level Manager")
	bool CooldownOver = true;
};
