// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

#include "BallPawn.generated.h"

UCLASS()
class ESCAPEBALL_API ABallPawn : public APawn
{
	GENERATED_BODY()

private:
	FVector prevLocation;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pawn Movement")
	float targetMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	float accelerationGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	float accelerationAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	float gravityForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	float jumpForce;			// How much up force.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Movement")
	float dragForce;			// How much up force.

	

	// Components
	UParticleSystemComponent* ourParticaleSystem;
	class UBallPawnMovementComponent* ourMovementComponent;
	USphereComponent* sphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Mesh")
	class UStaticMeshComponent* sphereVisual;

	USpringArmComponent* SpringArm;
	UCameraComponent* Camera;

	// Sets default values for this pawn's properties
	ABallPawn(const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	virtual void PostInitializeComponents() override;

	virtual void PostInitProperties() override;

	// Movement Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void Jump();
	void ParticleToggle();
	
};
