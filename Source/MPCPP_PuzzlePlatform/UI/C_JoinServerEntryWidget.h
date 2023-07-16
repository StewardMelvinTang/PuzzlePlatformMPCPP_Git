// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_MainMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MPCPP_PuzzlePlatform/UI/C_MainMenuWidget.h"
#include "C_JoinServerEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MPCPP_PUZZLEPLATFORM_API UC_JoinServerEntryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;


public:
	//Getter
	UButton* GetButton(){return BTN_Button;}
	UTextBlock* GetServerNameText(){return TXT_ServerName;}

	void Setup(class UC_MainMenuWidget* mainMenuWidgetRef, uint32 index);
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* BTN_Button;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TXT_ServerName;

private:
	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY()
	class UC_MainMenuWidget* mainMenuRef = nullptr;

	int32 id;
	
};
