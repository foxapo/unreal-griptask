// Radek Cehak | Interview Task | Grip Digital


#include "UnitFrameWidget.h"
#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Components/AttributeComponent.h"
#include "Components/ProgressBar.h"

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

void UUnitFrameWidget::InitTarget(TScriptInterface<ITargetInterface> Target)
{
	if (Target == nullptr)
	{
		bIsPlayer = false;
		CurrentTarget = nullptr;
		return;
	}

	CurrentTarget = Target;
	if (CurrentTarget->GetAttributeComponent())
	{
		bIsPlayer = true;
		CurrentTarget->GetAttributeComponent()->OnHealthChanged.AddDynamic(this, &UUnitFrameWidget::UpdateHealth);
		CurrentTarget->GetAttributeComponent()->OnManaChanged.AddDynamic(this, &UUnitFrameWidget::UpdateMana);
		UpdateHealth(CurrentTarget->GetAttributeComponent()->GetMaxHealth());
		UpdateMana(CurrentTarget->GetAttributeComponent()->GetMaxMana());
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

void UUnitFrameWidget::UpdateHealth(float Health)
{
	if (!bIsPlayer)
	{
		return;
	}
	TargetHealthPercent = Health / CurrentTarget->GetAttributeComponent()->GetMaxHealth();
}

void UUnitFrameWidget::UpdateMana(float Mana)
{
	if (!bIsPlayer)
	{
		return;
	}
	TargetManaPercent = Mana / CurrentTarget->GetAttributeComponent()->GetMaxMana();
}
