// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIPTASK_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void UpdateTimeText() const;

	const float MINIMAP_TIME_UPDATE_INTERVAL = 1.0f;
	const FString TIME_FORMAT = TEXT("%H:%M:%S");
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* MapBackgroundColor;

	UPROPERTY(EditAnywhere, Category = "Minimap")
	FLinearColor MapColor;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MinimapTimeText;

private:
	FTimerHandle TimerHandle;
};
