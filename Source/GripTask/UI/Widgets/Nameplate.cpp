// Radek Cehak | Interview Task | Grip Digital


#include "Nameplate.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Interfaces/TargetInterface.h"

void UNameplate::NativeConstruct()
{
	Super::NativeConstruct();
	SelectionFrame->SetVisibility(ESlateVisibility::Hidden);
}

void UNameplate::UpdateHealth(float Health)
{
	HealthBar->SetPercent(Health / Target.GetInterface()->GetAttributeComponent()->GetMaxHealth());
	CurrentHealth->SetText(FText::FromString(FString::FromInt(Health)));
}

void UNameplate::UpdateMana(float Mana)
{
}

void UNameplate::UpdateName(const FString& Value)
{
	Name->SetText(FText::FromString(Value));
}

void UNameplate::UpdateLevel(int8 Value)
{
	Level->SetText(FText::FromString(FString::FromInt(Value)));
}

void UNameplate::InitTarget(TScriptInterface<ITargetInterface> TargetInterface)
{
	Target = TargetInterface;
	if (UAttributeComponent* AttributeComponent = Target.GetInterface()->GetAttributeComponent())
	{
		UpdateHealth(AttributeComponent->GetMaxHealth());
		UpdateName(AttributeComponent->GetBaseStats().CharacterName);
		UpdateLevel(AttributeComponent->GetBaseStats().Level);
		MaxHealth->SetText(FText::FromString(FString::FromInt(AttributeComponent->GetMaxHealth())));
		AttributeComponent->OnHealthChanged.AddDynamic(this, &UNameplate::UpdateHealth);
	}

	if (UTargetComponent* TargetComponent = Target.GetInterface()->GetActorTargetComponent())
	{
		TargetComponent->OnSelected.AddDynamic(this, &UNameplate::Select);
		TargetComponent->OnDeselected.AddDynamic(this, &UNameplate::Deselect);
	}
}

void UNameplate::Select()
{
	SelectionFrame->SetVisibility(ESlateVisibility::Visible);
}

void UNameplate::Deselect()
{
	SelectionFrame->SetVisibility(ESlateVisibility::Hidden);
}

FReply UNameplate::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// Get PlayerController
		AGripTaskCharacter* Player = Cast<AGripTaskCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Player)
		{
			// Get TargetComponent
			UTargetComponent* TargetComponent = Player->GetActorTargetComponent();
			if (TargetComponent)
			{
				// Set target
				TargetComponent->SetTarget(Target.GetObject());
			}
		}

		return FReply::Handled();
	}

	return Reply;
}
