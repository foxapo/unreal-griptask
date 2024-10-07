// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GripTaskGameMode.generated.h"

UCLASS(minimalapi)
class AGripTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGripTaskGameMode();

protected:
	virtual void BeginPlay() override;
};
