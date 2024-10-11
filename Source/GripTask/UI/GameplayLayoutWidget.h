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
	void SetQuestMenu(bool bQuestMenuVisible) const;
	void SetInventoryMenu(bool bInventoryMenuVisible) const;
	
	FORCEINLINE UUnitFrameWidget* GetPlayerUnitFrameWidget() const { return PlayerUnitFrameWidget; }
	FORCEINLINE UUnitFrameWidget* GetTargetUnitFrameWidget() const { return TargetUnitFrameWidget; }
	FORCEINLINE UMinimapWidget* GetMinimapWidget() const { return MinimapWidget; }
	
protected:
	UFUNCTION()
	void InitializePlayerWidgets();
	void SubscribeTargetChange(TScriptInterface<ITargetInterface> PlayerTargetInterface);

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UUnitFrameWidget> PlayerUnitFrameClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<UUnitFrameWidget> TargetUnitFrameClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UMinimapWidget> MinimapWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UQuestMenu> QuestMenuClass;

	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UInventoryMenu> InventoryMenuClass;

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

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* InventoryMenuSlot;

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
	void InitializeInventoryMenu();

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

	UPROPERTY(BlueprintReadOnly, Category="Player Widgets", meta = (AllowPrivateAccess = "true"))
	class UInventoryMenu* InventoryMenuWidget;
};
