// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MPCPP_PUZZLEPLATFORM_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	UC_GameInstance();
	virtual void Init() override;

	//Exec compatible to PlayerCOntrollers, HUDs, Possessed Pawns, Cheat Managers, GameModes, Game Instances (Global)
	UFUNCTION(Exec) //Exec so it can be called in Execute Console Command
	void HostGame();

	UFUNCTION(Exec)
	void JoinGame(const FString &address);

protected:
	UPROPERTY(EditDefaultsOnly)
	ULevel* gameLevel;
	
};
