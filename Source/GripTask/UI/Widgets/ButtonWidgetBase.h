// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ButtonWidgetBase.generated.h"

class UTextWidgetBase;
class UButton;
/**
 * 
 */
UCLASS()
class GRIPTASK_API UButtonWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	UPROPERTY(meta = (BindWidget))
	UTextWidgetBase* ButtonText;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnButtonHovered();
	UFUNCTION()
	void SetButtonClickHandler();
	UFUNCTION()
	void OnButtonClicked();
};
