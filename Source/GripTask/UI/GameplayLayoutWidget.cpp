// Radek Cehak | Interview Task | Grip Digital


#include "GameplayLayoutWidget.h"
#include "Components/NamedSlot.h"
#include "GripTask/Core/DebugMacros.h"
#include "Widgets/MinimapWidget.h"
#include "Widgets/UnitFrameWidget.h"


// native construct
void UGameplayLayoutWidget::NativeConstruct()
{
	Super::NativeConstruct();
	InitializePlayerWidgets();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay layout widget initialized"));
	}
}


void UGameplayLayoutWidget::InitializePlayerWidgets()
{
	InitializePlayerUnitFrameWidget();
	InitializeTargetUnitFrameWidget();
	InitializeMinimapWidget();
}


void UGameplayLayoutWidget::InitializeMinimapWidget()
{
	if (!MinimapWidgetClass)
	{
		DEBUG_PRINT("Minimap widget class not set");
	}

	MinimapWidget = CreateWidget<UMinimapWidget>(GetWorld(), MinimapWidgetClass);
	if (MinimapWidget)
	{
		MinimapSlot->AddChild(MinimapWidget);
		DEBUG_PRINT("Minimap widget initialized");
	}
	else
	{
		DEBUG_PRINT("Minimap widget not initialized");
	}
}

void UGameplayLayoutWidget::InitializePlayerUnitFrameWidget()
{
	if (!PlayerUnitFrameClass)
	{
		DEBUG_PRINT("Player unit frame widget class not set");
	}

	PlayerUnitFrameWidget = CreateWidget<UUnitFrameWidget>(GetWorld(), PlayerUnitFrameClass);
	if (PlayerUnitFrameWidget)
	{
		PlayerUnitFrameSlot->AddChild(PlayerUnitFrameWidget);
		DEBUG_PRINT("Player unit frame widget initialized");
	}
	else
	{
		DEBUG_PRINT("Player unit frame widget not initialized");
	}
}

void UGameplayLayoutWidget::InitializeTargetUnitFrameWidget()
{
	if (!TargetUnitFrameClass)
	{
		DEBUG_PRINT("Target unit frame widget class not set");
	}

	TargetUnitFrameWidget = CreateWidget<UUnitFrameWidget>(GetWorld(), TargetUnitFrameClass);
	if (TargetUnitFrameWidget)
	{
		TargetUnitFrameSlot->AddChild(TargetUnitFrameWidget);
		DEBUG_PRINT("Target unit frame widget initialized");
	}
	else
	{
		DEBUG_PRINT("Target unit frame widget not initialized");
	}
}
