// Fill out your copyright notice in the Description page of Project Settings.

#include "StandingPawn.h"
#include "Engine/Scene.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/InputComponent.h"

// Sets default values
AStandingPawn::AStandingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//true als Default. Somit wird zuerst nach oben geflogen, wenn fliegen enabled ist
	FlyUpwards = true;
	FlyDistance = 0;

	MovingWithLeftController = false;
	MovingWithRightController = false;

}

// Called when the game starts or when spawned
void AStandingPawn::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
}

// Called every frame
void AStandingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleFlying();
	HandleMovement();
}

//Bewegung in Z-Richtung
void AStandingPawn::HandleFlying() 
{
	if (Flying)
	{
		if (FlyUpwards)
		{
			FVector CurrentLocation = this->GetActorLocation();
			CurrentLocation.Set(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + 0.1);
			this->SetActorLocation(CurrentLocation);
			FlyDistance++;
			//Richtungswechsel
			if (FlyDistance == 50)
			{
				FlyUpwards = !FlyUpwards;
				FlyDistance = 0;
			}
		}
		else
		{
			FVector CurrentLocation = this->GetActorLocation();
			CurrentLocation.Set(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z - 0.1);
			this->SetActorLocation(CurrentLocation);
			FlyDistance++;
			//Richtungswechsel
			if (FlyDistance == 50)
			{
				FlyUpwards = !FlyUpwards;
				FlyDistance = 0;
			}
		}
	}
}

//Bewegung in X- und Y-Richtung
void AStandingPawn::HandleMovement() 
{
	FVector Direction = FVector(0, 0, 0);
	//Hier werden drei Szenarien unterschieden. Nur linker oder rechter Controller oder beide
	if (MovingWithLeftController && !MovingWithRightController)
	{
		Direction = LeftController->GetForwardVector();
	}
	else if (!MovingWithLeftController && MovingWithRightController)
	{
		Direction = RightController->GetForwardVector();
	}
	else if (MovingWithLeftController && MovingWithRightController)
	{
		Direction = RightController->GetForwardVector() + LeftController->GetForwardVector();
	}

	FVector CurrentPosition = this->GetActorLocation();
	FVector NewPosition = FVector(CurrentPosition.X + Direction.X, CurrentPosition.Y + Direction.Y, CurrentPosition.Z);
	this->SetActorLocation(NewPosition);
}

// Called to bind functionality to input
void AStandingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftTouchpadPress", EInputEvent::IE_Pressed, this, &AStandingPawn::MotionControllerLeftTouchpadPressed);
	PlayerInputComponent->BindAction("LeftTouchpadPress", EInputEvent::IE_Released, this, &AStandingPawn::MotionControllerLeftTouchpadReleased);
	PlayerInputComponent->BindAction("RightTouchpadPress", EInputEvent::IE_Pressed, this, &AStandingPawn::MotionControllerRightTouchpadPressed);
	PlayerInputComponent->BindAction("RightTouchpadPress", EInputEvent::IE_Released, this, &AStandingPawn::MotionControllerRightTouchpadReleased);

}

void AStandingPawn::MotionControllerLeftTouchpadPressed()
{
	MovingWithLeftController = true;
}

void AStandingPawn::MotionControllerLeftTouchpadReleased()
{
	MovingWithLeftController = false;
}

void AStandingPawn::MotionControllerRightTouchpadPressed()
{
	MovingWithRightController = true;
}

void AStandingPawn::MotionControllerRightTouchpadReleased()
{
	MovingWithRightController = false;
}

