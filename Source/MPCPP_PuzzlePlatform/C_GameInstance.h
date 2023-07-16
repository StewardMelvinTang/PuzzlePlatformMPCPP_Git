// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "Engine/GameInstance.h"
#include "MPCPP_PuzzlePlatform/Actors/C_PlatformTrigger.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UI/C_MainMenuWidget.h"
#include "C_GameInstance.generated.h"


/**
 * 
 */
UCLASS()
class MPCPP_PUZZLEPLATFORM_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	UC_GameInstance();
	virtual void Init() override;

public:
	//Exec compatible to PlayerCOntrollers, HUDs, Possessed Pawns, Cheat Managers, GameModes, Game Instances (Global)
	UFUNCTION(Exec, BlueprintCallable) //Exec so it can be called in Execute Console Command
	void HostGame();

	UFUNCTION()
	void OnCreatedSession(FName name, bool isSuccess);

	UFUNCTION()
	void OnDestroyedSession(FName sessionName, bool isSuccess);

	UFUNCTION()
	void OnFoundSession(bool isSuccess);

	UFUNCTION(Exec, BlueprintCallable)
	void JoinGame(const FString &address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void SetInputGame();

	void CreateSession();
	void SearchSessions();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULevel> gameLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties", DisplayName = "WBP Main Menu")
	TSubclassOf<UUserWidget> Class_mainmenuWBP = nullptr;

private:
	UPROPERTY()
	UC_MainMenuWidget* mainmenuWBPRef = nullptr;

	//Cache
	IOnlineSubsystem* onlineSubsystem;
	IOnlineSessionPtr sessionInterface;
	TSharedPtr<class FOnlineSessionSearch> sessionSearchResult;
	
};
