// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeBall.h"
#include "BallPawnMovementComponent.h"


UBallPawnMovementComponent::UBallPawnMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set some defaults
	targetMoveSpeed = 500.0f;
	accelerationGround = 0.35f;
	accelerationAir = 0.15f;
	gravityForce = 16.0f;
	jumpForce = 500.0f;
	dragForce = 0.95f;

	
		
}


void UBallPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector DesiredMovementThisFrame;

		
	// Make sure that everyting is still valid and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime) || !UpdatedComponent->IsRegistered())
	{
		return;
	}
	
	// Get the velocity of the object by comparing its current location to its previous.
	FVector presentLocation = UpdatedComponent->GetComponentLocation();
	FVector curVelocity = (presentLocation - prevLocation) / DeltaTime;

	FVector newVelocity;
	

	//FVector downVelocity = FVector(0.0f, 0.0f, newVelocity.Z);
	FVector downVector = FVector(0.0f, 0.0f, -8.0f);

	// check if the object is on the ground.

	UWorld* worldRef = UpdatedComponent->GetWorld();

	FHitResult hitGround;
	FOverlapResult overGround;

	FCollisionQueryParams colParams = FCollisionQueryParams();
	colParams.bFindInitialOverlaps = false;

	//bool isOverlapping

	bool result = worldRef->SweepSingle(hitGround, UpdatedComponent->GetComponentLocation(), UpdatedComponent->GetComponentLocation() + (downVector),
		UpdatedComponent->GetComponentRotation().Quaternion(), FCollisionShape::MakeSphere(40.0f), colParams, FCollisionObjectQueryParams::FCollisionObjectQueryParams(ECC_WorldStatic | ECC_WorldDynamic));


	if (result)
	{

		newVelocity.X = curVelocity.X - (curVelocity.X *(dragForce * DeltaTime));
		newVelocity.Y = curVelocity.Y - (curVelocity.Y *(dragForce * DeltaTime));
		newVelocity.Z = curVelocity.Z - (gravityForce* DeltaTime);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("True")));
		if (newVelocity.Size() < targetMoveSpeed)
		{
			DesiredMovementThisFrame = (ConsumeInputVector().GetClampedToMaxSize(1.0f) * accelerationGround) + (newVelocity * DeltaTime);
		}
		else
		{
			ConsumeInputVector(); // Consume... but don't use.
			DesiredMovementThisFrame = (newVelocity * DeltaTime);

		}

		if (doJump)
		{
			hitGround.Normal;

			DesiredMovementThisFrame += hitGround.Normal *(jumpForce * DeltaTime);
		}

	}
	else
	{
		newVelocity.X = curVelocity.X;
		newVelocity.Y = curVelocity.Y;
		newVelocity.Z = curVelocity.Z - (gravityForce* DeltaTime);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("False")));

		if (newVelocity.Size() < targetMoveSpeed)
		{
			DesiredMovementThisFrame = (ConsumeInputVector().GetClampedToMaxSize(1.0f) * accelerationAir) + (newVelocity * DeltaTime);
		}
		else
		{
			ConsumeInputVector(); // Consume... but don't use.
			DesiredMovementThisFrame = (newVelocity * DeltaTime);

		}
	}



	DesiredMovementThisFrame = DesiredMovementThisFrame.GetClampedToMaxSize(3000.0f);



	if (true)//!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;

		// We need to test if the pawn is on the ground or not.


		// before we do the actual move, store pawn location for the next frame.
		prevLocation = UpdatedComponent->GetComponentLocation();



		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);

		}
	}
	

	doJump = false;


	
}

void UBallPawnMovementComponent::PostInitProperties()
{
	Super::PostInitProperties();

	//prevLocation = UpdatedComponent->GetComponentLocation();
}





