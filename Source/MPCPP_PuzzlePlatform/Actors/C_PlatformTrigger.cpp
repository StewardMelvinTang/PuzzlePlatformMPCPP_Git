// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/Actors/C_PlatformTrigger.h"

// Sets default values
AC_PlatformTrigger::AC_PlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
