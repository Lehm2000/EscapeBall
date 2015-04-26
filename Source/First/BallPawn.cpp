// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeBall.h"
#include "BallPawn.h"
#include "BallPawnMovementComponent.h"


// Sets default values
ABallPawn::ABallPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set some defaults
	targetMoveSpeed = 500.0f;
	accelerationGround = 0.35f;
	accelerationAir = 0.15f;
	gravityForce = 16.0f;
	jumpForce = 500.0f;
	dragForce = 0.95f;

	// Our root component will be a sphere that reacts to physics
	sphereComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,TEXT("RootComponent"));
	RootComponent = sphereComponent;
	sphereComponent->InitSphereRadius(40.0f);
	sphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	
	
	// Create and position a mesh component so we can see where our sphere is
	sphereVisual = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this,TEXT("VisualRepresentation"));
	sphereVisual->AttachTo(RootComponent);
	
	// Create a particle system that we can activate or deactivate
	/*ourParticaleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	ourParticaleSystem->AttachTo(sphereVisual);
	ourParticaleSystem->bAutoActivate = false;
	ourParticaleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		ourParticaleSystem->SetTemplate(ParticleAsset.Object);
	}*/

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this,TEXT("CameraAttachmentArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-30.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	

	// Create a camera and attach to our spring arm
	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("ActualCamera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	// Take control of the default player
	// AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our movement component, and tell it to update the root
	
	ourMovementComponent = ObjectInitializer.CreateDefaultSubobject<UBallPawnMovementComponent>(this, TEXT("CustomMovementComponent"));
	ourMovementComponent->UpdatedComponent = RootComponent;
	
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// set prev location to be current location
	prevLocation = RootComponent->GetComponentLocation();
	ourMovementComponent->prevLocation = RootComponent->GetComponentLocation();
	
}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );


	// rotate sphere based on movement
	FVector presentLocation = RootComponent->GetComponentLocation();

	// get the difference in location
	FVector moveVector = presentLocation - prevLocation;

	float moveDist = moveVector.Size();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("moveSpeed: %f"), moveDist / DeltaTime));

	moveVector.Normalize();

	// Draw move direction line
	DrawDebugLine(GetWorld(), presentLocation, presentLocation + (moveVector * 200.0f), FColor(255, 0, 0),false,-1.0f,0,5.0f);

	// create a vector for up
	FVector up = FVector(0.0f, 0.0f, 1.0f);

	// Draw up direction line
	DrawDebugLine(GetWorld(), presentLocation, presentLocation + (up * 200.0f), FColor(0, 255, 0), false, -1.0f, 0, 5.0f);

	FVector rotationAxis = FVector::CrossProduct(moveVector, up);

	// Draw rotation axis
	DrawDebugLine(GetWorld(), presentLocation, presentLocation + (rotationAxis * 200.0f), FColor(0, 0, 255), false, -1.0f, 0, 5.0f);

	FRotator axisRotator = rotationAxis.Rotation();
	
	
	
	FQuat axisQuat = FQuat(rotationAxis, moveDist/-125.6f);
	
	sphereVisual->AddWorldRotation(axisQuat.Rotator());

	// set the presentLocation to be the previous location
	prevLocation = presentLocation;

	
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ABallPawn::ParticleToggle);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::Jump);

	InputComponent->BindAxis("MoveLateral", this, &ABallPawn::MoveForward);
	InputComponent->BindAxis("MoveHorizontal", this, &ABallPawn::MoveRight);
	InputComponent->BindAxis("CameraYaw", this, &ABallPawn::Turn);

}

UPawnMovementComponent* ABallPawn::GetMovementComponent() const
{
	return ourMovementComponent;
}

void ABallPawn::MoveForward(float AxisValue)
{
	if (ourMovementComponent && (ourMovementComponent->UpdatedComponent == RootComponent))
	{
		ourMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue );
	}
}

void ABallPawn::MoveRight(float AxisValue)
{
	if (ourMovementComponent && (ourMovementComponent->UpdatedComponent == RootComponent))
	{
		ourMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ABallPawn::Turn(float AxisValue)
{
	FRotator newRotation = GetActorRotation();
	newRotation.Yaw += AxisValue;
	SetActorRotation(newRotation);
}

void ABallPawn::ParticleToggle()
{
	if (ourParticaleSystem && ourParticaleSystem->Template)
	{
		ourParticaleSystem->Activate(!ourParticaleSystem->IsActive());
	}
}

void ABallPawn::Jump()
{
	if (ourMovementComponent && (ourMovementComponent->UpdatedComponent == RootComponent))
	{
		ourMovementComponent->doJump = true;
	}
}


// Called after constructor
void ABallPawn::PostInitProperties()
{

	Super::PostInitProperties();
		
}

void ABallPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ourMovementComponent->targetMoveSpeed = targetMoveSpeed;
	ourMovementComponent->accelerationGround = accelerationGround;
	ourMovementComponent->accelerationAir = accelerationAir;
	ourMovementComponent->gravityForce = gravityForce;
	ourMovementComponent->jumpForce = jumpForce;
	ourMovementComponent->dragForce = dragForce;
		
}

