// Radek Cehak | Interview Task | Grip Digital


#include "GameplayLayoutWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/NamedSlot.h"
#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MinimapWidget.h"
#include "Widgets/UnitFrameWidget.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "Widgets/QuestMenu.h"

void UGameplayLayoutWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay layout widget initialized"));
	}

	InitializePlayerWidgets();
}

void UGameplayLayoutWidget::SetQuestMenu(const bool bQuestMenuVisible) const
{
	if (QuestMenuWidget)
	{
		QuestMenuWidget->SetVisibility(bQuestMenuVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
	else
	{
		DEBUG_PRINT("Quest menu widget not found");
	}
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
	OnTargetChanged(false);
	if (PlayerTargetInterface->GetActorTargetComponent())
	{
		PlayerTargetInterface->GetActorTargetComponent()->SetPlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		PlayerTargetInterface->GetActorTargetComponent()->OnTargetChanged.AddDynamic(this, &UGameplayLayoutWidget::OnTargetChanged);
	}
	else
	{
		DEBUG_PRINT("Player target component not found");
	}

	InitializeQuestMenu();
}

void UGameplayLayoutWidget::SetPlayerFrame(TScriptInterface<ITargetInterface> Target)
{
	PlayerUnitFrameWidget->InitTarget(Target);
}

void UGameplayLayoutWidget::SetTargetFrame(TScriptInterface<ITargetInterface> Target)
{
	TargetUnitFrameWidget->InitTarget(Target);
}

void UGameplayLayoutWidget::OnTargetChanged(bool bIsTarget)
{
	if (bIsTarget)
	{
		SetTargetFrame(PlayerCharacter->GetActorTargetComponent()->GetCurrentTarget());
		TargetUnitFrameWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TargetUnitFrameWidget->SetVisibility(ESlateVisibility::Hidden);
		SetTargetFrame(nullptr);
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

void UGameplayLayoutWidget::InitializeQuestMenu()
{
	if (!QuestMenuClass)
	{
		DEBUG_PRINT("Quest menu widget class not set");
		return;
	}

	QuestMenuWidget = CreateWidget<UQuestMenu>(GetWorld(), QuestMenuClass);
	// PlayerQuestLogSlot->AddChild(QuestMenuWidget);
	// Add QuestMenuWidget to the viewport
	PlayerQuestLogSlot->AddChild(QuestMenuWidget);
	// QuestMenuWidget->SetDesiredSizeInViewport(FVector2D(640.0f, 480.0f));
	QuestMenuWidget->SetVisibility(ESlateVisibility::Hidden);
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
