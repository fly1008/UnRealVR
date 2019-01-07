// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "MotionController.generated.h"

/**
 * 
 */
UCLASS()
class TOOLKIT_CODEBASIERT_API UMyMotionController : public UMotionControllerComponent
{
	GENERATED_BODY()
	
public:
	UMyMotionController();

	USceneComponent* HeldObjectLocation;
	bool isHolding;

	virtual void PickUpObject();
	virtual void DropObject();	

private:
	UPrimitiveComponent* HitComponent;
	AActor* PickedUpActor;
	
};
