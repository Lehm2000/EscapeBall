// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeBall.h"
#include "EscapeBallGameMode.h"

#include "DestinationGoal.h"

void AEscapeBallGameMode::StartPlay()
{
	Super::StartPlay();

	// Initialize some variables

	totalGameTime = 0.0f;

	// Do other stuff

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}

	

	for (TActorIterator<ADestinationGoal> destItr(GetWorld()); destItr; ++destItr)
	{
		goal = *destItr;
	}

	if (GEngine  && goal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Found Goal"));
	}

	if (GEngine  && playerPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Found Player"));
	}

	// Spawn Pawn

}

void AEscapeBallGameMode::Tick(float DeltaSeconds)
{
	// Add time to the total Time
	totalGameTime += DeltaSeconds;

	FTimespan timeFormatter = FTimespan(0, 0, 0, FMath::Floor(totalGameTime), FMath::Floor(FMath::Fmod(totalGameTime, 1.0f)*1000.0f));
	totalGameTimeString = timeFormatter.ToString();

	// Check if player has touched the goal.

	UWorld* worldRef = GetWorld();

	//ADestinationGoal* goalRef = Cast<ADestinationGoal>(goal);

	if (goal && goal->isTriggered())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("Reached Goal"));

		UGameplayStatics::OpenLevel(GWorld, "LevelEditorQuickStartGuide", false, "");
	}

	
}




