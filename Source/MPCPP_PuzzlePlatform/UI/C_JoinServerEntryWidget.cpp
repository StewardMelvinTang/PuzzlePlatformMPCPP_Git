// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/UI/C_JoinServerEntryWidget.h"

void UC_JoinServerEntryWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UC_JoinServerEntryWidget::Setup(UC_MainMenuWidget* mainMenuWidgetRef, uint32 index) {
	mainMenuRef = mainMenuWidgetRef;
	id = index;
	BTN_Button->OnClicked.AddDynamic(this, &UC_JoinServerEntryWidget::OnButtonClicked);
}

void UC_JoinServerEntryWidget::OnButtonClicked() {
	if (!mainMenuRef) return;
	mainMenuRef->SelectIndex(id);
}
