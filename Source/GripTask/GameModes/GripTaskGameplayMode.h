// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GripTask/Data/FQuestData.h"
#include "GripTaskGameplayMode.generated.h"

struct FCharacterStats;
class UDataTable;
/**
 * 
 */
UCLASS()
class GRIPTASK_API AGripTaskGameplayMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	FCharacterStats* GetCharacterStats(FName RowName) const;
	TArray<FQuestData> GetQuestData() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay")
	UDataTable* CharacterStatsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gameplay")
	UDataTable* QuestDataTable;
};
