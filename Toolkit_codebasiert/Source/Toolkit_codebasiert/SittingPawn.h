// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllerUser.h"
#include "SittingPawn.generated.h"

UCLASS()
class TOOLKIT_CODEBASIERT_API ASittingPawn : public AControllerUser
{
	GENERATED_BODY()

private:
	FVector* CameraHeight;

public:
	// Sets default values for this pawn's properties
	ASittingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
