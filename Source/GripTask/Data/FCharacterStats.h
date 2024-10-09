#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCharacterStats.generated.h"


USTRUCT()
struct FCharacterStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Base Stats")
	float MaxHealth = 10;

	UPROPERTY(EditAnywhere, Category = "Base Stats")
	float MaxMana = 10;

	UPROPERTY(EditAnywhere, Category = "Base Stats")
	float NaturalManaRegen = 1;
};
