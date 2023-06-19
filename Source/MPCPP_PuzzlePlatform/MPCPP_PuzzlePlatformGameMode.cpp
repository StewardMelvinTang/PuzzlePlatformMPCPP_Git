// Copyright Epic Games, Inc. All Rights Reserved.

#include "MPCPP_PuzzlePlatformGameMode.h"
#include "MPCPP_PuzzlePlatformCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMPCPP_PuzzlePlatformGameMode::AMPCPP_PuzzlePlatformGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
