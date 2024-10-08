// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GripTaskGameplayMode.generated.h"

/**
 * 
 */
UCLASS()
class GRIPTASK_API AGripTaskGameplayMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
