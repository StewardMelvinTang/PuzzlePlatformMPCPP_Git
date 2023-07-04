// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_MovingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class MPCPP_PUZZLEPLATFORM_API AC_MovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_MovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsStepped(){return isStepped;}


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* platformMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* boxCollider = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* onSteppedMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = true), DisplayName = "Target Location")
	FVector targetLoc = FVector::ZeroVector;

	UFUNCTION(BlueprintCallable)
	void OnPlayerOverlapped(AActor* overlappedActor);

	UFUNCTION(BlueprintCallable)
	void OnPlayerUnoverlap(AActor* overlappedActor);

private:
	bool startMove = false;
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	bool isStepped = false;
	float lerpAlpha = 0.f;
	UPROPERTY()
	UMaterialInterface* defaultMaterial = nullptr;

};
