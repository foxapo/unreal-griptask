// Radek Cehak | Interview Task | Grip Digital

#include "QuestMenu.h"
#include "QuestMenuEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "GripTask/Classes/UQuestItemData.h"
#include "GripTask/Core/DebugMacros.h"
#include "GripTask/Core/GlobalUtils.h"
#include "GripTask/GameModes/GripTaskGameplayMode.h"
#include "GripTask/UI/HUDs/GameplayHUD.h"


void UQuestMenu::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UQuestMenu::CloseQuestMenu);

	if (AGripTaskGameplayMode* GameplayMode = Cast<AGripTaskGameplayMode>(GetWorld()->GetAuthGameMode()))
	{
		TArray<FQuestData> QuestData = GameplayMode->GetQuestData();
		TArray<UObject*> Data;

		for (const FQuestData& Quest : QuestData)
		{
			UQuestItemData* QuestItem = NewObject<UQuestItemData>(this);
			QuestItem->QuestName = Quest.QuestName;
			QuestItem->QuestIcon = Quest.QuestIcon;
			QuestItem->QuestDescription = Quest.QuestDescription;
			Data.Add(QuestItem);
		}

		QuestList->SetListItems(Data);
	}
}


void UQuestMenu::OnQuestSelected(UQuestItemData* QuestData)
{
	if (QuestData == nullptr)
	{
		ActiveQuestName->SetText(FText::FromString("No quest selected"));
		ActiveQuestIcon->SetVisibility(ESlateVisibility::Collapsed);
		ActiveQuestDescription->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	ActiveQuestName->SetText(FText::FromString(QuestData->QuestName));
	ActiveQuestIcon->SetBrushFromTexture(QuestData->QuestIcon);
	ActiveQuestDescription->SetText(FText::FromString(QuestData->QuestDescription));
	ActiveQuestIcon->SetVisibility(ESlateVisibility::Visible);
	ActiveQuestDescription->SetVisibility(ESlateVisibility::Visible);
}

void UQuestMenu::CloseQuestMenu()
{
	GlobalUtils::GetGameplayHUD(GetWorld())->ToggleQuestLog();
}

void UQuestMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DEBUG_PRINT("UQuestMenu::NativeOnInitialized");
	GlobalUtils::GetGameplayHUD(GetWorld())->OnQuestSelected.AddUObject(this, &UQuestMenu::OnQuestSelected);
	OnQuestSelected(nullptr);
}
