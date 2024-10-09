// Radek Cehak | Interview Task | Grip Digital


#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "UnitFrameWidget.h"
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

void UUnitFrameWidget::InitPlayer(AGripTaskCharacter* Player)
{
	Character = Player;
	if (Character->GetAttributeComponent())
	{
		Character->GetAttributeComponent()->OnHealthChanged.AddDynamic(this, &UUnitFrameWidget::UpdateHealth);
		Character->GetAttributeComponent()->OnManaChanged.AddDynamic(this, &UUnitFrameWidget::UpdateMana);
		UpdateHealth(Character->GetAttributeComponent()->GetMaxHealth());
		UpdateMana(Character->GetAttributeComponent()->GetMaxMana());
	}
}

void UUnitFrameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!Character)
	{
		return;
	}

	if (CurrentHealthPercent != TargetHealthPercent)
	{
		CurrentHealthPercent = FMath::FInterpTo(CurrentHealthPercent, TargetHealthPercent, InDeltaTime, InterpolationSpeed);
		HealthBar->SetPercent(CurrentHealthPercent);
	}

	if (CurrentManaPercent != TargetManaPercent)
	{
		CurrentManaPercent = FMath::FInterpTo(CurrentManaPercent, TargetManaPercent, InDeltaTime, InterpolationSpeed);
		ManaBar->SetPercent(CurrentManaPercent);
	}
}

void UUnitFrameWidget::UpdateHealth(float Health)
{
	TargetHealthPercent = Health / Character->GetAttributeComponent()->GetMaxHealth();
}

void UUnitFrameWidget::UpdateMana(float Mana)
{
	TargetManaPercent = Mana / Character->GetAttributeComponent()->GetMaxMana();
}
