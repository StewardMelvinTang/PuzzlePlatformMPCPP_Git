// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/UI/C_MainMenuWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "MPCPP_PuzzlePlatform/C_GameInstance.h"

void UC_MainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController) {
		FInputModeUIOnly inputModeUIOnly;
		inputModeUIOnly.SetWidgetToFocus(TakeWidget());
		inputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		playerController->SetInputMode(inputModeUIOnly);
		playerController->bShowMouseCursor = true;
	}

	gameInstance = GetGameInstance<UC_GameInstance>();

	if (BTN_HostGame) BTN_HostGame->OnClicked.AddDynamic(this, &UC_MainMenuWidget::HostGameBTN);
	if (BTN_JoinGameMM) BTN_JoinGameMM->OnClicked.AddDynamic(this, &UC_MainMenuWidget::JoinGameBTNMainMenu);
	if (BTN_JoinGame) BTN_JoinGame->OnClicked.AddDynamic(this, &UC_MainMenuWidget::JoinGameBTN);
	if (BTN_Refresh) BTN_Refresh->OnClicked.AddDynamic(this, &UC_MainMenuWidget::RefreshBtn);

	if (WS_MainSwitcher) WS_MainSwitcher->SetActiveWidgetIndex(0);
}

void UC_MainMenuWidget::GenerateServerList(FOnlineSessionSearchResult sessionSearchResult, uint32 index) {
	if (!SB_ServerList) return;
	SB_ServerList->ClearChildren();
	
	UC_JoinServerEntryWidget* entryWidget = CreateWidget<UC_JoinServerEntryWidget>(this, joinServerEntryWidget);
	if (!entryWidget) return;
	entryWidget->GetServerNameText()->SetText(FText::FromString(sessionSearchResult.GetSessionIdStr()));
	entryWidget->Setup(this, index);
	//entryWidget->GetButton()->OnClicked.AddDynamic()
	SB_ServerList->AddChild(entryWidget);
}

void UC_MainMenuWidget::HostGameBTN() {
	gameInstance->HostGame();
}

void UC_MainMenuWidget::JoinGameBTN() {
	if (selectedIndex.IsSet()) {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index : %d"), selectedIndex.GetValue());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not Set"));
	}
	
	gameInstance->JoinGame(TB_IpAddress->GetText().ToString());
}

void UC_MainMenuWidget::JoinGameBTNMainMenu() {
	WS_MainSwitcher->SetActiveWidgetIndex(1);
	gameInstance->SearchSessions();
}

void UC_MainMenuWidget::RefreshBtn() {
	gameInstance->SearchSessions();
}

