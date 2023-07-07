// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameInstance.h"

UC_GameInstance::UC_GameInstance() {
	UE_LOG(LogTemp, Display, TEXT("Game Instance Constructed"));
}

void UC_GameInstance::Init() {
	Super::Init();
	UE_LOG(LogTemp, Display, TEXT("Game Instance Initialized"));
}

void UC_GameInstance::HostGame() {
	UEngine* engine = GetEngine();
	if (!engine) return;
	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, "Game Host Called");
	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UC_GameInstance::JoinGame(const FString &address) {
	UEngine* engine = GetEngine();
	if (!engine) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Red, FString::Printf(TEXT("Game Joining : %s"), *address));
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!playerController) return;
	playerController->ClientTravel(address, TRAVEL_Absolute);
}
