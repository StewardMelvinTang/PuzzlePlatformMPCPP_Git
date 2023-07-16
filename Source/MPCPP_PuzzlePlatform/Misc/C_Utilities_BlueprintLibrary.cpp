// Fill out your copyright notice in the Description page of Project Settings.


#include "MPCPP_PuzzlePlatform/Misc/C_Utilities_BlueprintLibrary.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

//[EDITOR ONLY] This will show a small message toast in the bottom right
void UC_Utilities_BlueprintLibrary::ShowEditorToast(FString messageString) {
#if WITH_EDITOR
	FNotificationInfo Info(FText::FromString(messageString));
	Info.bFireAndForget = true;
	Info.ExpireDuration = 3.5f; // Duration in seconds

	FSlateNotificationManager::Get().AddNotification(Info);
#endif
}
