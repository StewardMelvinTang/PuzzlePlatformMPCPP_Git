// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/Actors/C_PlatformTrigger.h"

#include "C_MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AC_PlatformTrigger::AC_PlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));

	textRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	textRender->SetupAttachment(triggerVolume);
	textRender->SetText(FText::FromString("Test"));

	RootComponent = triggerVolume;
}

// Called when the game starts or when spawned
void AC_PlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AC_PlatformTrigger::OnPlayerOverlapped);
	triggerVolume->OnComponentEndOverlap.AddDynamic(this, &AC_PlatformTrigger::OnPlayerDeOverlapped);
}

// Called every frame
void AC_PlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PlatformTrigger::OnPlayerOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Activated"));

	for (AC_MovingPlatform* platform : movingPlatforms) {
		platform->AddActiveTrigger();
	}
}

void AC_PlatformTrigger::OnPlayerDeOverlapped(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
	for (AC_MovingPlatform* platform : movingPlatforms) {
		platform->RemoveActiveTrigger();
	}
}

