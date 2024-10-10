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
	UPROPERTY(EditAnywhere, Category = "Base Stats")	
	UTexture2D* CharacterSprite;
	UPROPERTY(EditAnywhere, Category = "Base Stats")
	FString CharacterName;
	UPROPERTY(EditAnywhere, Category = "Base Stats")
	int8 Level = 1;
};
