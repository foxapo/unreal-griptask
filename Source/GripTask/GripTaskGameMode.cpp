// Copyright Epic Games, Inc. All Rights Reserved.

#include "GripTaskGameMode.h"
#include "GripTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGripTaskGameMode::AGripTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
