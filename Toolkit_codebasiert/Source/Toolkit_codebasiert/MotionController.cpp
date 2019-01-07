#include "MotionController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UMyMotionController::UMyMotionController()
{
	HeldObjectLocation = CreateDefaultSubobject<USceneComponent>(TEXT("HeldObjectLocation"));
	FVector* Location = new FVector(38, 0, 0);
	HeldObjectLocation->SetRelativeLocation(*Location, false, nullptr, ETeleportType::None);

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Engine/VREditor/Devices/Vive/VivePreControllerMesh.mesh"));
	UStaticMesh* Asset = MeshAsset.Object;
	Mesh->SetStaticMesh(Asset);

	Mesh->SetupAttachment(this);
}


void UMyMotionController::PickUpObject()
{
	FVector WorldLocation = GetComponentLocation();
	FVector ForwardVector = GetForwardVector();
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

		HitComponent = HComponent;
		if (HitComponent->IsAnySimulatingPhysics())
		{
			PickedUpActor = HitActor;
			HitComponent->SetSimulatePhysics(false);
			EAttachmentRule InLocationRule = EAttachmentRule::SnapToTarget;
			EAttachmentRule InRotationRule = EAttachmentRule::SnapToTarget;
			EAttachmentRule InScaleRule = EAttachmentRule::KeepWorld;
			FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(InLocationRule, InRotationRule, InScaleRule, true);
			HitComponent->AttachToComponent(HeldObjectLocation, AttachmentRules, FName());
			isHolding = true;
		}
	}
}

void UMyMotionController::DropObject()
{
	if (IsValid(PickedUpActor))
	{
		EDetachmentRule LocationRule = EDetachmentRule::KeepWorld;
		EDetachmentRule RotationRule = EDetachmentRule::KeepWorld;
		EDetachmentRule ScaleRule = EDetachmentRule::KeepWorld;
		FDetachmentTransformRules Rules = FDetachmentTransformRules(LocationRule, RotationRule, ScaleRule, false);
		PickedUpActor->DetachFromActor(Rules);

		if (IsValid(HitComponent))
		{
			HitComponent->SetSimulatePhysics(true);
			isHolding = false;
			HitComponent = nullptr;
			PickedUpActor = nullptr;
		}
	}
}
