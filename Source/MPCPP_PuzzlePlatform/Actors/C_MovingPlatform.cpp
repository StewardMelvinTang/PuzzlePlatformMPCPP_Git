// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/Actors/C_MovingPlatform.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MPCPP_PuzzlePlatform/MPCPP_PuzzlePlatformCharacter.h"

// Sets default values
AC_MovingPlatform::AC_MovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	platformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Static Mesh"));
	platformMesh->SetMobility(EComponentMobility::Movable);
	RootComponent = platformMesh;

	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	boxCollider->SetupAttachment(platformMesh);	
}

// Called when the game starts or when spawned
void AC_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//Set Actor Replication
	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	
	defaultMaterial = platformMesh->GetMaterial(0);
	GlobalTargetLocation = GetTransform().TransformPosition(targetLoc);
	GlobalStartLocation = GetActorLocation();
}

// Called every frame
void AC_MovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (activeTriggers > 0) {
		if (canMove && platformMesh) {
			FVector Location = GetActorLocation();
			float DistanceLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float DistanceTravelled = (Location - GlobalStartLocation).Size();
			UE_LOG(LogTemp, Display, TEXT("Distance Length : %f, Distance Travelled : %f"), DistanceLength, DistanceTravelled);

			if (DistanceTravelled >= DistanceLength) {
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}
}

void AC_MovingPlatform::OnPlayerOverlapped(AActor* overlappedActor) {
	if (Cast<AMPCPP_PuzzlePlatformCharacter>(overlappedActor)) {
		isStepped = true;
		platformMesh->SetMaterial(0, onSteppedMaterial);
	}
}

void AC_MovingPlatform::OnPlayerUnoverlap(AActor* overlappedActor) {
	if (Cast<AMPCPP_PuzzlePlatformCharacter>(overlappedActor)) {
		isStepped = false;
		TArray<AActor*>overlappingActors;
		boxCollider->GetOverlappingActors(overlappingActors, AMPCPP_PuzzlePlatformCharacter::StaticClass());
		if (overlappingActors.Num() > 0) return;
		platformMesh->SetMaterial(0, defaultMaterial);
	}
}

void AC_MovingPlatform::AddActiveTrigger() {
	activeTriggers++;
}

void AC_MovingPlatform::RemoveActiveTrigger() {
	if (activeTriggers > 0) activeTriggers--;
}


