// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UQuestItemData.generated.h"

UCLASS(Blueprintable)
class GRIPTASK_API UQuestItemData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Quest Data")
	FString QuestName;

	UPROPERTY(BlueprintReadWrite, Category = "Quest Data")
	UTexture2D* QuestIcon;

	UPROPERTY(BlueprintReadWrite, Category = "Quest Data")
	FString QuestDescription;
};
