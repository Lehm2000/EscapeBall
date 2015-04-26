// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeBall.h"
#include "BallStart.h"

ABallStart::ABallStart(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	//SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraAttachmentArm"));
	//CapsuleComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("StartCapsule"));
	CapsuleComponent->SetCapsuleRadius(10.0f);
}




