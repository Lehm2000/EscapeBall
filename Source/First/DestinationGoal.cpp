// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeBall.h"
#include "DestinationGoal.h"


// Sets default values
ADestinationGoal::ADestinationGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set variables
	triggered = false;

	goalSize = FVector(50.0f,50.0f, 50.0f);

	// Set up root component for collision
	// Our root component will be a sphere that reacts to physics
	UBoxComponent* rootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	rootBox->InitBoxExtent(goalSize);
	rootBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RootComponent = rootBox;

	// Create and position a cube mesh component so we can see where our sphere is
	boxVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	FVector boxScale = goalSize / 50.0f;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Cube"));
	boxVisual->SetStaticMesh(MeshObj.Object);

	boxVisual->SetWorldScale3D(boxScale);
	boxVisual->SetCollisionProfileName(TEXT("NoCollision"));

	const ConstructorHelpers::FObjectFinder<UMaterial> MeshMat(TEXT("/Game/Materials/RedGoal"));
	boxVisual->SetMaterial(0,MeshMat.Object);
	boxVisual->AttachTo(RootComponent);

	
	
}

// Called when the game starts or when spawned
void ADestinationGoal::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ADestinationGoal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	

}

#if WITH_EDITOR
void ADestinationGoal::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UBoxComponent* rootBox = Cast<UBoxComponent>(RootComponent);
	rootBox->SetBoxExtent(goalSize);

	FVector boxScale = goalSize / 50.0f;
	boxVisual->SetWorldScale3D(boxScale);

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void ADestinationGoal::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Triggered"));
	triggered = true;
}



// Accessors and Modifiers
bool ADestinationGoal::isTriggered()
{
	return triggered;
}

