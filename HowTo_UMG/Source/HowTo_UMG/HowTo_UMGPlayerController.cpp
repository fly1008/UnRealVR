// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_UMGPlayerController.h"

void AHowTo_UMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}


