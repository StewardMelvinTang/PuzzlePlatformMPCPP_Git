// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_JoinServerEntryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "C_MainMenuWidget.generated.h"

class UWidgetSwitcher;
class UC_GameInstance;
/**
 * 
 */
UCLASS()
class MPCPP_PUZZLEPLATFORM_API UC_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta =(BindWidgetOptional))
	UButton* BTN_HostGame;
	UPROPERTY(meta =(BindWidgetOptional))
	UButton* BTN_JoinGame;
	UPROPERTY(meta =(BindWidgetOptional))
	UButton* BTN_JoinGameMM;
	UPROPERTY(meta =(BindWidgetOptional))
	UButton* BTN_Refresh;
	UPROPERTY(meta = (BindWidgetOptional))
	UWidgetSwitcher* WS_MainSwitcher;
	UPROPERTY(meta=(BindWidgetOptional))
	UEditableTextBox* TB_IpAddress;
	UPROPERTY(meta=(BindWidgetOptional))
	UScrollBox* SB_ServerList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UC_JoinServerEntryWidget> joinServerEntryWidget;

	void GenerateServerList(class FOnlineSessionSearchResult sessionSearchResult, uint32 index);

	void SelectIndex(uint32 newIndex) {selectedIndex = newIndex;}
	
private:
	UPROPERTY()
	APlayerController* playerController = nullptr;

	UPROPERTY()
	UC_GameInstance* gameInstance = nullptr;

	//Click Delegate
	UFUNCTION()
	void HostGameBTN();

	UFUNCTION()
	void JoinGameBTN();

	UFUNCTION()
	void JoinGameBTNMainMenu();

	UFUNCTION()
	void RefreshBtn();

	UFUNCTION()
	void OnServerEntryBTNClicked();

	
	TOptional<uint32> selectedIndex;
	
};
