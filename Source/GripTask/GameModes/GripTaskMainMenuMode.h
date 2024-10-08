// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GripTaskMainMenuMode.generated.h"

UCLASS(minimalapi)
class AGripTaskMainMenuMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGripTaskMainMenuMode();

protected:
	virtual void BeginPlay() override;
};
