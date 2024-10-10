// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "HUDs/GameplayHUD.h"
#include "GameplayLayoutWidget.generated.h"

class UCanvasPanel;
class AGripTaskCharacter;
class UMinimapWidget;
class UUnitFrameWidget;
class UNamedSlot;
class UQuestMenu;


/**
 * Main gameplay layout widget that is created in the GameplayHUD 
 */
UCLASS()
class GRIPTASK_API UGameplayLayoutWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UUnitFrameWidget* GetPlayerUnitFrameWidget() const { return PlayerUnitFrameWidget; }
	UUnitFrameWidget* GetTargetUnitFrameWidget() const { return TargetUnitFrameWidget; }
	UMinimapWidget* GetMinimapWidget() const { return MinimapWidget; }
	void SetQuestMenu(bool bQuestMenuVisible) const;

protected:
	UFUNCTION()
	void InitializePlayerWidgets();

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UUnitFrameWidget> PlayerUnitFrameClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<UUnitFrameWidget> TargetUnitFrameClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UMinimapWidget> MinimapWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UQuestMenu> QuestMenuClass;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* PlayerUnitFrameSlot;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* TargetUnitFrameSlot;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* MinimapSlot;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* PlayerQuestLogSlot;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

private:
	TWeakObjectPtr<AGripTaskCharacter> PlayerCharacter;

	UFUNCTION()
	void InitializeMinimapWidget();

	UFUNCTION()
	void InitializeTargetUnitFrameWidget();

	UFUNCTION()
	void InitializePlayerUnitFrameWidget();

	UFUNCTION()
	void InitializeQuestMenu();

	UFUNCTION()
	void SetPlayerFrame(TScriptInterface<ITargetInterface> Target);

	UFUNCTION()
	void SetTargetFrame(TScriptInterface<ITargetInterface> Target);

	UFUNCTION()
	void OnTargetChanged(bool bIsTarget);

	UPROPERTY(BlueprintReadOnly, Category="Player Widgets", meta = (AllowPrivateAccess = "true"))
	class UUnitFrameWidget* PlayerUnitFrameWidget;

	UPROPERTY(BlueprintReadOnly, Category="Player Widgets", meta = (AllowPrivateAccess = "true"))
	class UUnitFrameWidget* TargetUnitFrameWidget;

	UPROPERTY(BlueprintReadOnly, Category="Player Widgets", meta = (AllowPrivateAccess = "true"))
	class UMinimapWidget* MinimapWidget;

	UPROPERTY(BlueprintReadOnly, Category="Player Widgets", meta = (AllowPrivateAccess = "true"))
	class UQuestMenu* QuestMenuWidget;
};
