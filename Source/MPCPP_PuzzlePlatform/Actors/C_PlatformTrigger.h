// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlatformTrigger.generated.h"

class AC_MovingPlatform;
class UTextRenderComponent;
class UBoxComponent;

UCLASS()
class MPCPP_PUZZLEPLATFORM_API AC_PlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* triggerVolume;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* textRender;

	UPROPERTY(EditAnywhere)
	TArray<AC_MovingPlatform*> movingPlatforms;
	
	//Delegates
	UFUNCTION()
	void OnPlayerOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerDeOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
