// Fill out your copyright notice in the Description page of Project Settings.

#include "SittingPawn.h"
#include "Engine/Scene.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
ASittingPawn::ASittingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));

	Camera->SetupAttachment(CameraRoot);
	CameraHeight = new FVector(0, 0, 121);
}

// Called when the game starts or when spawned
void ASittingPawn::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
	CameraRoot->SetRelativeLocation(*CameraHeight, false, nullptr, ETeleportType::None);
}

// Called every frame
void ASittingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASittingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

