// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButtonWidgetBase;
class UCanvasPanel;

UCLASS()
class GRIPTASK_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category="Bindings")
	UButtonWidgetBase* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category="Bindings")
	UButtonWidgetBase* ExitButton;

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();
};
