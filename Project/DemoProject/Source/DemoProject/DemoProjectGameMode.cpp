// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DemoProjectGameMode.h"
#include "DemoProjectHUD.h"
#include "DemoProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADemoProjectGameMode::ADemoProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADemoProjectHUD::StaticClass();
}
