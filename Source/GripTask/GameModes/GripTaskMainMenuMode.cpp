// Copyright Epic Games, Inc. All Rights Reserved.

#include "GripTaskMainMenuMode.h"
#include "UObject/ConstructorHelpers.h"

AGripTaskMainMenuMode::AGripTaskMainMenuMode()
{
}

void AGripTaskMainMenuMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MainMenu BeginPlay"));
	}
	
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}
