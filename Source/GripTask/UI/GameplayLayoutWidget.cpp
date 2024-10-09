// Radek Cehak | Interview Task | Grip Digital


#include "GameplayLayoutWidget.h"
#include "Components/NamedSlot.h"
#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MinimapWidget.h"
#include "Widgets/UnitFrameWidget.h"
#include "GripTask/Interfaces/UTargetInterface.h"

void UGameplayLayoutWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay layout widget initialized"));
	}

	InitializePlayerWidgets();
}

void UGameplayLayoutWidget::InitializePlayerWidgets()
{
	PlayerCharacter = Cast<AGripTaskCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter.IsValid())
	{
		DEBUG_PRINT("Player character not found");
		return;
	}

	InitializePlayerUnitFrameWidget();
	InitializeTargetUnitFrameWidget();
	InitializeMinimapWidget();

	TScriptInterface<ITargetInterface> PlayerTargetInterface;
	PlayerTargetInterface.SetObject(PlayerCharacter.Get());
	PlayerTargetInterface.SetInterface(Cast<ITargetInterface>(PlayerCharacter));
	SetPlayerFrame(PlayerTargetInterface);
}

void UGameplayLayoutWidget::SetPlayerFrame(const TScriptInterface<ITargetInterface>& Target) const
{
	PlayerUnitFrameWidget->InitTarget(Target);
}

void UGameplayLayoutWidget::SetTargetFrame(const TScriptInterface<ITargetInterface>& Target) const
{
	TargetUnitFrameWidget->InitTarget(Target);
}

void UGameplayLayoutWidget::OnTargetChanged(bool bIsTarget) const
{
	if (bIsTarget)
	{
		SetTargetFrame(PlayerCharacter->GetActorTargetComponent()->GetCurrentTarget());
		TargetUnitFrameWidget->Toggle(true);
	}
	else
	{
		SetTargetFrame(nullptr);
		TargetUnitFrameWidget->Toggle(false);
	}
}

// * WIDGET INITIALIZATION * //

void UGameplayLayoutWidget::InitializePlayerUnitFrameWidget()
{
	if (!PlayerUnitFrameClass)
	{
		DEBUG_PRINT("Player unit frame widget class not set");
		return;
	}

	PlayerUnitFrameWidget = CreateWidget<UUnitFrameWidget>(GetWorld(), PlayerUnitFrameClass);
	PlayerUnitFrameSlot->AddChild(PlayerUnitFrameWidget);
}

void UGameplayLayoutWidget::InitializeTargetUnitFrameWidget()
{
	if (!TargetUnitFrameClass)
	{
		DEBUG_PRINT("Target unit frame widget class not set");
	}

	if (!TargetUnitFrameWidget)
	{
		TargetUnitFrameWidget = CreateWidget<UUnitFrameWidget>(GetWorld(), TargetUnitFrameClass);
	}

	if (TargetUnitFrameWidget)
	{
		TargetUnitFrameSlot->AddChild(TargetUnitFrameWidget);
	}
	else
	{
		DEBUG_PRINT("Target unit frame widget not initialized");
	}
}

// * MINIMAP * //

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
