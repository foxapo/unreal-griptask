#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FQuestData.generated.h"



USTRUCT()
struct FQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Quest Data")
	FString QuestName;

	UPROPERTY(EditAnywhere, Category = "Quest Data")
	FString QuestDescription;

	UPROPERTY(EditAnywhere, Category = "Quest Data")
	UTexture2D* QuestIcon;
};
