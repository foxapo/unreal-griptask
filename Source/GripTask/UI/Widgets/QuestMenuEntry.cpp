// Radek Cehak | Interview Task | Grip Digital


#include "QuestMenuEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GripTask/Classes/UQuestItemData.h"
#include "GripTask/Core/GlobalUtils.h"
#include "GripTask/UI/HUDs/GameplayHUD.h"


void UQuestMenuEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	QuestData = Cast<UQuestItemData>(ListItemObject);
	QuestName->SetText(FText::FromString(QuestData->QuestName));
	QuestIcon->SetBrushFromTexture(QuestData->QuestIcon);
	Background->SetColorAndOpacity(GlobalUtils::GetGameplayHUD(GetWorld())->EntryNormalColor);
}

FReply UQuestMenuEntry::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		Background->SetColorAndOpacity(GlobalUtils::GetGameplayHUD(GetWorld())->EntrySelectedColor);
		GlobalUtils::GetGameplayHUD(GetWorld())->OnQuestSelected.Broadcast(QuestData);
		return FReply::Handled();
	}
	return Reply;
}

void UQuestMenuEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Get HUD from the GameMode
	Background->SetColorAndOpacity(GlobalUtils::GetGameplayHUD(GetWorld())->EntryHoveredColor);
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UQuestMenuEntry::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Background->SetColorAndOpacity(GlobalUtils::GetGameplayHUD(GetWorld())->EntryNormalColor);
	Super::NativeOnMouseLeave(InMouseEvent);
}
