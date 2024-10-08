// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"


class APlayerController;
/**
 * 
 */
UCLASS()
class GRIPTASK_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;
};
