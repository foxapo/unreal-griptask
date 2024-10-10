// Radek Cehak | Interview Task | Grip Digital


#include "UnitFrameWidget.h"
#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Delegates/DelegateCombinations.h"
#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Components/AttributeComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUnitFrameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HealthBar->SetPercent(0);
	ManaBar->SetPercent(0);
	CurrentHealthPercent = 0;
	TargetHealthPercent = 0;
}

void UUnitFrameWidget::Toggle(bool State)
{
	if (State)
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUnitFrameWidget::UnsubscribeTarget()
{
	if (CurrentTarget && CurrentTarget->GetAttributeComponent())
	{
		CurrentTarget->GetAttributeComponent()->OnHealthChanged.RemoveDynamic(this, &UUnitFrameWidget::UpdateHealth);
		CurrentTarget->GetAttributeComponent()->OnManaChanged.RemoveDynamic(this, &UUnitFrameWidget::UpdateMana);
	}
	// CurrentHealthPercent = 0;
	// HealthBar->SetPercent(CurrentHealthPercent);
	// CurrentManaPercent = 0;
	// ManaBar->SetPercent(CurrentManaPercent);
	CurrentTarget = nullptr;
}

void UUnitFrameWidget::SubscribeTarget()
{
	if (CurrentTarget && CurrentTarget->GetAttributeComponent())
	{
		bIsPlayer = true;
		CurrentTarget->GetAttributeComponent()->OnHealthChanged.AddDynamic(this, &UUnitFrameWidget::UpdateHealth);
		CurrentTarget->GetAttributeComponent()->OnManaChanged.AddDynamic(this, &UUnitFrameWidget::UpdateMana);
		UpdateHealth(CurrentTarget->GetAttributeComponent()->GetMaxHealth());
		UpdateMana(CurrentTarget->GetAttributeComponent()->GetMaxMana());
		UpdateName(CurrentTarget->GetAttributeComponent()->GetBaseStats().CharacterName);
		UpdatePortrait(CurrentTarget->GetAttributeComponent()->GetBaseStats().CharacterSprite);
		UpdateLevel(CurrentTarget->GetAttributeComponent()->GetBaseStats().Level);
	}
}

void UUnitFrameWidget::InitTarget(TScriptInterface<ITargetInterface> Target)
{
	if (Target == nullptr)
	{
		bIsPlayer = false;
		UnsubscribeTarget();
	}
	else
	{
		UnsubscribeTarget();
		CurrentTarget = Target;
		SubscribeTarget();
	}
}

void UUnitFrameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentTarget == nullptr)
	{
		bIsPlayer = false;
		return;
	}

	if (CurrentHealthPercent != TargetHealthPercent) // Prevents of updating the health bar when it's not needed
	{
		CurrentHealthPercent = FMath::FInterpTo(CurrentHealthPercent, TargetHealthPercent, InDeltaTime,
		                                        InterpolationSpeed);
		HealthBar->SetPercent(CurrentHealthPercent);
	}

	if (CurrentManaPercent != TargetManaPercent) // Prevents of updating the mana bar when it's not needed
	{
		CurrentManaPercent = FMath::FInterpTo(CurrentManaPercent, TargetManaPercent, InDeltaTime, InterpolationSpeed);
		ManaBar->SetPercent(CurrentManaPercent);
	}
}

void UUnitFrameWidget::UpdateHealth(const float Health)
{
	if (!bIsPlayer)
	{
		return;
	}
	TargetHealthPercent = Health / CurrentTarget->GetAttributeComponent()->GetMaxHealth();
	HealthValue->SetText(FText::FromString(FString::Printf(
		TEXT("%d / %d"), static_cast<int>(Health),
		static_cast<int>(CurrentTarget->GetAttributeComponent()->GetMaxHealth()))));;
}

void UUnitFrameWidget::UpdateMana(const float Mana)
{
	if (!bIsPlayer)
	{
		return;
	}
	TargetManaPercent = Mana / CurrentTarget->GetAttributeComponent()->GetMaxMana();
	ManaValue->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), static_cast<int>(Mana),
	                                                     static_cast<int>(CurrentTarget->GetAttributeComponent()->
		                                                     GetMaxMana()))));
}

void UUnitFrameWidget::UpdateName(const FString& Name) const
{
	if (!bIsPlayer)
	{
		return;
	}
	NameText->SetText(FText::FromString(Name));
}

void UUnitFrameWidget::UpdatePortrait(UTexture2D* Portrait) const
{
	if (!bIsPlayer)
	{
		return;
	}
	PlayerPortrait->SetBrushFromTexture(Portrait);
}

void UUnitFrameWidget::UpdateLevel(int8 Level) const
{
	if (!bIsPlayer)
	{
		return;
	}
	LevelValue->SetText(FText::FromString(FString::Printf(TEXT("%d"), Level)));
}
