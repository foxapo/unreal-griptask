// Radek Cehak | Interview Task | Grip Digital


#include "MinimapWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MinimapTimeText)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMinimapWidget::UpdateTimeText, UMinimapWidget::MINIMAP_TIME_UPDATE_INTERVAL, true);
	}

	if (MapBackgroundColor)
	{
		MapBackgroundColor->SetColorAndOpacity(MapColor);
	}

	UpdateTimeText();
}

void UMinimapWidget::NativeDestruct()
{
	if (TimerHandle.IsValid() && GetWorld())
	{
		// Unsubscribe the timer from the world if necessary
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	Super::NativeDestruct();
}

void UMinimapWidget::UpdateTimeText() const
{
	if (MinimapTimeText)
	{
		const FDateTime CurrentTime = FDateTime::Now();
		const FString TimeString = CurrentTime.ToString(*TIME_FORMAT);
		MinimapTimeText->SetText(FText::FromString(TimeString));
	}
}

