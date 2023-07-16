// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MPCPP_PuzzlePlatform/Misc/C_Utilities_BlueprintLibrary.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

static const FName SESSION_NAME = TEXT("SessionTest");
UC_GameInstance::UC_GameInstance() {
	UE_LOG(LogTemp, Display, TEXT("Game Instance Constructed"));
}

void UC_GameInstance::Init() {
	Super::Init();
	UE_LOG(LogTemp, Display, TEXT("Game Instance Initialized"));
	onlineSubsystem = IOnlineSubsystem::Get();
	if (!onlineSubsystem) UC_Utilities_BlueprintLibrary::ShowEditorToast("OSS is not enabled");
	sessionInterface = onlineSubsystem->GetSessionInterface();

	SearchSessions();

	if (!Class_mainmenuWBP) { 
		UC_Utilities_BlueprintLibrary::ShowEditorToast("Please Setup Required Classes in Game Instance");
	}
}

void UC_GameInstance::HostGame() {
	if (sessionInterface) {
		UC_Utilities_BlueprintLibrary::ShowEditorToast("Session Interface Found");
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UC_GameInstance::OnCreatedSession);
		sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UC_GameInstance::OnDestroyedSession);
		
		auto existingSession = sessionInterface->GetNamedSession(SESSION_NAME);
		
		if (existingSession != nullptr) {
			sessionInterface->DestroySession(SESSION_NAME);
		} else {
			CreateSession();
		}
	}
}

void UC_GameInstance::OnCreatedSession(FName name, bool isSuccess) {
	if (!isSuccess || name.IsNone()) return;
	UEngine* engine = GetEngine();
	if (!engine) return;
	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, "Game Host Called");
	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UC_GameInstance::OnDestroyedSession(FName sessionName, bool isSuccess) {
	if (isSuccess) {
		CreateSession();
	}
}

void UC_GameInstance::OnFoundSession(bool isSuccess) {
	if (isSuccess && sessionSearchResult.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Sessions Found"));

		uint32 i = 0;
		for (auto &searchResult : sessionSearchResult->SearchResults) {
			UE_LOG(LogTemp, Error, TEXT("Search Result: %s"), *searchResult.GetSessionIdStr());
			mainmenuWBPRef->GenerateServerList(searchResult, i);
			++i;
		}
	}
}

void UC_GameInstance::JoinGame(const FString &address) {
	UEngine* engine = GetEngine();
	if (!engine) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Red, FString::Printf(TEXT("Game Joining : %s"), *address));
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!playerController) return;
	playerController->ClientTravel(address, TRAVEL_Absolute);
}

void UC_GameInstance::LoadMenu() {
	if (!Class_mainmenuWBP) return;
	mainmenuWBPRef = CreateWidget<UC_MainMenuWidget>(this, Class_mainmenuWBP);
	mainmenuWBPRef->AddToViewport(0);
}

void UC_GameInstance::SetInputGame() {
	if (GetFirstLocalPlayerController(GetWorld())) {
		GetFirstLocalPlayerController(GetWorld())->bShowMouseCursor = false;
		FInputModeGameOnly newInputMode;
		GetFirstLocalPlayerController(GetWorld())->SetInputMode(newInputMode);
	}
}

void UC_GameInstance::CreateSession() {
	FOnlineSessionSettings sessionSettings;
	sessionSettings.bIsLANMatch = true;
	sessionSettings.NumPublicConnections = 2;
	sessionSettings.bShouldAdvertise = true;
	sessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
}

void UC_GameInstance::SearchSessions() {
	sessionSearchResult = MakeShareable(new FOnlineSessionSearch());
	sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UC_GameInstance::OnFoundSession);
	sessionInterface->FindSessions(0, sessionSearchResult.ToSharedRef());
}
