// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "testGameMode.h"
#include "testHUD.h"
#include "testCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtestGameMode::AtestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AtestHUD::StaticClass();
}
