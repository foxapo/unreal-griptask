// Radek Cehak | Interview Task | Grip Digital
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TextWidgetBase.generated.h"

class UTextBlock;

UCLASS()
class GRIPTASK_API UTextWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;

	// Function to set text
	UFUNCTION(BlueprintCallable, Category = "Text Widget")
	void SetText(FText NewText);
};
