// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UCanvasPanel;
class UButton;
/**
 * 
 */
UCLASS()
class GRIPTASK_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget), Category="Bindings")
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget), Category="Bindings")
	class UButton* ExitButton;

	UFUNCTION()
	void OnStartButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();
};
