// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GripTask/Classes/UQuestItemData.h"
#include "GripTask/UI/Widgets/Nameplate.h"
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
	UPROPERTY(EditAnywhere, Category="Quest Menu")
	FLinearColor EntryHoveredColor;

	UPROPERTY(EditAnywhere, Category="Quest Menu")
	FLinearColor EntryNormalColor;

	UPROPERTY(EditAnywhere, Category="Quest Menu")
	FLinearColor EntrySelectedColor;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestSelected, UQuestItemData*);
	FOnQuestSelected OnQuestSelected;

	virtual void BeginPlay() override;
	void ToggleQuestLog();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<class UGameplayLayoutWidget> GameplayLayoutWidgetClass;
	UPROPERTY()
	class UGameplayLayoutWidget* GameplayLayoutWidget;

private:
	bool bQuestMenuVisible = false;
};
