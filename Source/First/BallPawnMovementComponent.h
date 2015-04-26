// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

#include "BallPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEBALL_API UBallPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	
	
public:

	// Variables
	float targetMoveSpeed;		// Speed for the movement to target.  Can exceed this if outside forces act upon component... but player input cannot drive it faster.
	float accelerationGround;
	float accelerationAir;
	float gravityForce;
	float jumpForce;			// How much up force.
	float dragForce;			// how much drag... typically between 0 and 1.

	bool doJump;				// attempt jump?
	
	FVector prevLocation;		// where was the pawn on the last frame.

		
	UBallPawnMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void PostInitProperties() override;

};
