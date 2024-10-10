// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "QuestMenuEntry.generated.h"

class UQuestItemData;
class UImage;
struct FQuestData;
class UTextBlock;

UCLASS()
class GRIPTASK_API UQuestMenuEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	// Slate widget style
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Menu Entry")
	FButtonStyle ButtonStyle;

	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

	FORCEINLINE UQuestItemData* GetQuestData() const { return QuestData; }

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestName;

	UPROPERTY(meta = (BindWidget))
	UImage* QuestIcon;

	class UQuestItemData* QuestData;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
