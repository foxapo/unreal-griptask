// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "DraggableWidgetBase.h"
#include "QuestMenu.generated.h"

struct FQuestData;
class UQuestItemData;
class UListView;

UCLASS()
class GRIPTASK_API UQuestMenu : public UDraggableWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Player Widgets")
	TSubclassOf<class UQuestMenuEntry> QuestMenuEntryClass;

protected:
	UPROPERTY(meta = (BindWidget))
	UListView* QuestList;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ActiveQuestName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ActiveQuestDescription;

	UPROPERTY(meta = (BindWidget))
	class UImage* ActiveQuestIcon;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UFUNCTION()
	void OnQuestSelected(UQuestItemData* QuestData);

	UFUNCTION()
	void CloseQuestMenu();
};
