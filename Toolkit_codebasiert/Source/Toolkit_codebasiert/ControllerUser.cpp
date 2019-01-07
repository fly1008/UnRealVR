// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerUser.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

AControllerUser::AControllerUser()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AControllerUser::BeginPlay()
{
	Super::BeginPlay();
}


void AControllerUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AControllerUser::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Motion controller bindings
	PlayerInputComponent->BindAction("LeftTrigger", EInputEvent::IE_Pressed, this, &AControllerUser::MotionControllerLeftTriggerPressed);
	PlayerInputComponent->BindAction("LeftTrigger", EInputEvent::IE_Released, this, &AControllerUser::MotionControllerLeftTriggerReleased);
	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AControllerUser::MotionControllerRightTriggerPressed);
	PlayerInputComponent->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AControllerUser::MotionControllerRightTriggerReleased);
}

void AControllerUser::MotionControllerLeftTriggerPressed()
{
	if (!LeftController->isHolding)
	{
		LeftController->PickUpObject();
	}
}

void AControllerUser::MotionControllerLeftTriggerReleased()
{
	LeftController->DropObject();
}

void AControllerUser::MotionControllerRightTriggerPressed()
{
	if (!RightController->isHolding) 
	{
		RightController->PickUpObject();
	}
}

void AControllerUser::MotionControllerRightTriggerReleased()
{
	RightController->DropObject();
}
