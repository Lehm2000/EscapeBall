// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestinationGoal.generated.h"

UCLASS()
class ESCAPEBALL_API ADestinationGoal : public AActor
{
	GENERATED_BODY()

	// variables
	bool triggered;
	
public:	

	// Properties
	UPROPERTY(EditAnywhere)
	FVector goalSize;

	UPROPERTY()
	UStaticMeshComponent* boxVisual;

	// Sets default values for this actor's properties
	ADestinationGoal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called when property changed in editor.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;

	// Accessors and Modifiers
	bool isTriggered();

	
	
};
