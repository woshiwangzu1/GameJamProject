// Copyright Epic Games, Inc. All Rights Reserved.

#include "CandyGameMode.h"
#include "CandyCharacter.h"
#include "UI/SugerHUD.h"
#include "UObject/ConstructorHelpers.h"

ACandyGameMode::ACandyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = ASugerHUD::StaticClass();
}
