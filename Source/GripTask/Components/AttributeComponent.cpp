﻿// Radek Cehak | Interview Task | Grip Digital


#include "AttributeComponent.h"
#include "GripTask/Core/DebugMacros.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAttributeComponent::NotifyHealthChanged() const
{
	OnHealthChanged.Broadcast(CurrentHealth);
}

void UAttributeComponent::NotifyManaChanged() const
{
	OnManaChanged.Broadcast(CurrentMana);
}

void UAttributeComponent::SetBaseStats(const FCharacterStats* Stats)
{
	BaseStats = *Stats;
	CurrentHealth = MaxHealth = BaseStats.MaxHealth;
	CurrentMana = MaxMana = BaseStats.MaxMana;
	NaturalManaRegen = BaseStats.NaturalManaRegen;
	NotifyHealthChanged();
	NotifyManaChanged();
}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RegenerateMana(DeltaTime);
}

void UAttributeComponent::ConsumeMana(const float Value)
{
	if (CurrentMana - Value < 0)
	{
		CurrentMana = 0;
	}
	else
	{
		CurrentMana -= Value;
	}

	NotifyManaChanged();
}

// JUST TESTING METHODS (OF COURSE THIS COULD BE DONE MORE COMPLEX AND WITH MORE FEATURES)

void UAttributeComponent::ApplyDamage(float Value)
{
	CurrentHealth -= Value;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
	}
	NotifyHealthChanged();
}

void UAttributeComponent::ApplyHeal(float Value)
{
	CurrentHealth += Value;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
	NotifyHealthChanged();
}

FName UAttributeComponent::GetId() const
{
	return CharacterStatsId;
}

void UAttributeComponent::RegenerateMana(float DeltaTime)
{
	if (CurrentMana < MaxMana)
	{
		CurrentMana += NaturalManaRegen * DeltaTime;
	}
	LastManaRegenTime += DeltaTime;
	if (LastManaRegenTime >= ManaRegenNotifyInterval)
	{
		NotifyManaChanged();
		LastManaRegenTime = 0;
	}
}
