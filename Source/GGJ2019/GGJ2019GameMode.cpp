// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GGJ2019GameMode.h"
#include "GGJ2019Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ2019GameMode::AGGJ2019GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
