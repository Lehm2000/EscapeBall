// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"

#include "DestinationGoal.h"


#include "EscapeBallGameMode.generated.h"



/**
 * 
 */
UCLASS()
class ESCAPEBALL_API AEscapeBallGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	// variables
	AActor* playerPawn;
	ADestinationGoal* goal;

	UPROPERTY(BlueprintReadOnly)
	float totalGameTime;

	UPROPERTY(BlueprintReadOnly)
	FString totalGameTimeString;


	// Game Functions
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
};
