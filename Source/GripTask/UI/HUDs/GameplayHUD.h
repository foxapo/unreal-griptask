// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayHUD.generated.h"

class APlayerController;
/**
 * 
 */
UCLASS()
class GRIPTASK_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<class UGameplayLayoutWidget> GameplayLayoutWidgetClass;

	UPROPERTY()
	class UGameplayLayoutWidget* GameplayLayoutWidget;
};
