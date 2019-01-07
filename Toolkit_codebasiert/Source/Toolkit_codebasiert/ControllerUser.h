// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionController.h"
#include "GameFramework/Pawn.h"
#include "HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "ControllerUser.generated.h"

/**
 * Standardklasse für PAwns, die mit den Motion-Controllern agieren sollen
 */
UCLASS()
class TOOLKIT_CODEBASIERT_API AControllerUser : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AControllerUser();

	UMyMotionController* LeftController;
	UMyMotionController* RightController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void MotionControllerLeftTriggerPressed();

	UFUNCTION()
	virtual void MotionControllerLeftTriggerReleased();

	UFUNCTION()
	virtual void MotionControllerRightTriggerPressed();

	UFUNCTION()
	virtual void MotionControllerRightTriggerReleased();
};
