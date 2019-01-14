// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerUser.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

AControllerUser::AControllerUser()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	Camera->SetupAttachment(CameraRoot);

	InitController();
}

void AControllerUser::InitController()
{
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	HeldObjectLocationR = CreateDefaultSubobject<USceneComponent>(TEXT("HeldObjectLocationR"));
	HeldObjectLocationL = CreateDefaultSubobject<USceneComponent>(TEXT("HeldObjectLocationL"));

	LeftController->SetupAttachment(CameraRoot);
	RightController->SetupAttachment(CameraRoot);

	RightController->SetTrackingMotionSource(FName("Right"));

	UStaticMeshComponent* MeshL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshL"));
	UStaticMeshComponent* MeshR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshR"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAssetL(TEXT("StaticMesh'/Engine/VREditor/Devices/Vive/VivePreControllerMesh.VivePreControllerMesh'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAssetR(TEXT("StaticMesh'/Engine/VREditor/Devices/Vive/VivePreControllerMesh.VivePreControllerMesh'"));
	UStaticMesh* AssetL = MeshAssetL.Object;
	UStaticMesh* AssetR = MeshAssetR.Object;
	MeshR->SetStaticMesh(AssetR);
	MeshL->SetStaticMesh(AssetL);

	MeshR->SetupAttachment(RightController);
	MeshL->SetupAttachment(LeftController);

	HeldObjectLocationR->SetupAttachment(RightController);
	HeldObjectLocationL->SetupAttachment(LeftController);
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
	if (!isHoldingL)
	{
		PickUpObject(*LeftController);
	}
}

void AControllerUser::MotionControllerLeftTriggerReleased()
{
	DropObject(*LeftController);
}

void AControllerUser::MotionControllerRightTriggerPressed()
{
	if (!isHoldingR) 
	{
		PickUpObject(*RightController);
	}
}

void AControllerUser::MotionControllerRightTriggerReleased()
{
	DropObject(*RightController);
}

void AControllerUser::PickUpObject(UMotionControllerComponent &Controller)
{
	FVector WorldLocation = Controller.GetComponentLocation();
	FVector ForwardVector = Controller.GetForwardVector();
	FVector EndVector = (ForwardVector * 1000) + WorldLocation;
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
	FHitResult OutHit;
	bool result = UKismetSystemLibrary::LineTraceSingleForObjects(this, WorldLocation, EndVector, TraceObjects, false, TArray<AActor*>(),
		EDrawDebugTrace::ForDuration, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.0F);

	if (result)
	{
		//Definieren der Outputvariablen von BreakHitResult
		bool BlockingHit;
		bool InitialOverlap;
		float Time;
		float Distance;
		FVector Location;
		FVector ImpactPoint;
		FVector Normal;
		FVector ImpactNormal;
		UPhysicalMaterial* PhysMat;
		AActor* HitActor;
		UPrimitiveComponent* HComponent;
		FName HitBoneName;
		int32 HitItem;
		int32 FaceIndex;
		FVector TraceStart;
		FVector TraceEnd;
		UGameplayStatics::BreakHitResult(OutHit, BlockingHit, InitialOverlap, Time, Distance, Location, ImpactPoint, Normal, ImpactNormal, PhysMat, HitActor,
			HComponent, HitBoneName, HitItem, FaceIndex, TraceStart, TraceEnd);

		if (Controller.GetFName().Compare(RightController->GetFName()) == 0) {
			HitComponentR = HComponent;
			if (HitComponentR->IsAnySimulatingPhysics())
			{
				PickedUpActorR = HitActor;
				HitComponentR->SetSimulatePhysics(false);
				EAttachmentRule InLocationRule = EAttachmentRule::SnapToTarget;
				EAttachmentRule InRotationRule = EAttachmentRule::SnapToTarget;
				EAttachmentRule InScaleRule = EAttachmentRule::KeepWorld;
				FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(InLocationRule, InRotationRule, InScaleRule, true);
				HitComponentR->AttachToComponent(HeldObjectLocationR, AttachmentRules, FName());
				isHoldingR = true;
			}
		}
		else 
		{
			HitComponentL = HComponent;
			if (HitComponentL->IsAnySimulatingPhysics())
			{
				PickedUpActorL = HitActor;
				HitComponentL->SetSimulatePhysics(false);
				EAttachmentRule InLocationRule = EAttachmentRule::SnapToTarget;
				EAttachmentRule InRotationRule = EAttachmentRule::SnapToTarget;
				EAttachmentRule InScaleRule = EAttachmentRule::KeepWorld;
				FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(InLocationRule, InRotationRule, InScaleRule, true);
				HitComponentL->AttachToComponent(HeldObjectLocationL, AttachmentRules, FName());
				isHoldingL = true;
			}
		}
	}
}

void AControllerUser::DropObject(UMotionControllerComponent &Controller)
{
	if (Controller.GetFName().Compare(RightController->GetFName()) == 0)
	{
		if (IsValid(PickedUpActorR))
		{
			EDetachmentRule LocationRule = EDetachmentRule::KeepWorld;
			EDetachmentRule RotationRule = EDetachmentRule::KeepWorld;
			EDetachmentRule ScaleRule = EDetachmentRule::KeepWorld;
			FDetachmentTransformRules Rules = FDetachmentTransformRules(LocationRule, RotationRule, ScaleRule, false);
			PickedUpActorR->DetachFromActor(Rules);

			if (IsValid(HitComponentR))
			{
				HitComponentR->SetSimulatePhysics(true);
				isHoldingR = false;
				HitComponentR = nullptr;
				PickedUpActorR = nullptr;
			}
		}
	}
	else
	{
		if (IsValid(PickedUpActorL))
		{
			EDetachmentRule LocationRule = EDetachmentRule::KeepWorld;
			EDetachmentRule RotationRule = EDetachmentRule::KeepWorld;
			EDetachmentRule ScaleRule = EDetachmentRule::KeepWorld;
			FDetachmentTransformRules Rules = FDetachmentTransformRules(LocationRule, RotationRule, ScaleRule, false);
			PickedUpActorL->DetachFromActor(Rules);

			if (IsValid(HitComponentL))
			{
				HitComponentL->SetSimulatePhysics(true);
				isHoldingL = false;
				HitComponentL = nullptr;
				PickedUpActorL = nullptr;
			}
		}
	}
}