// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerUser.h"
#include "StandingPawn.generated.h"

UCLASS()
class TOOLKIT_CODEBASIERT_API AStandingPawn : public AControllerUser
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStandingPawn();

private:
	
	bool FlyUpwards;
	int FlyDistance;

	//Nur der stehende Pawn soll sich bewegen können. Im Sitzen macht das keinen Sinn
	bool MovingWithRightController;
	bool MovingWithLeftController;

	virtual void HandleMovement();
	virtual void HandleFlying();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	bool Flying;
	
	UFUNCTION()
	virtual void MotionControllerLeftTouchpadPressed();

	UFUNCTION()
	virtual void MotionControllerLeftTouchpadReleased();

	UFUNCTION()
	virtual void MotionControllerRightTouchpadPressed();

	UFUNCTION()
	virtual void MotionControllerRightTouchpadReleased();
};
