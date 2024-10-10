// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GripTask/Data/FCharacterStats.h"
#include "AttributeComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRIPTASK_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();
	FName GetCharacterStatsId() const { return CharacterStatsId; }
	void SetBaseStats(const FCharacterStats* Stats);
	FCharacterStats GetBaseStats() const { return BaseStats; }
	void RegenerateMana(float DeltaTime);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	float GetHealth() const { return CurrentHealth; }
	float GetMana() const { return CurrentMana; }
	float GetMaxHealth() const { return MaxHealth; }
	float GetMaxMana() const { return MaxMana; }
	float GetNaturalManaRegen() const { return NaturalManaRegen; }
	void ConsumeMana(float Value);
	FName GetId() const;

	// EVENTS
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, Mana);

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnManaChanged OnManaChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Character stat id
	UPROPERTY(EditAnywhere, Category="Attributes")
	FName CharacterStatsId;

	void NotifyHealthChanged() const;
	void NotifyManaChanged() const;

private:
	UPROPERTY(BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	FCharacterStats BaseStats;
	float CurrentHealth = 0;
	float CurrentMana = 0;
	float MaxHealth = 0;
	float MaxMana = 0;
	float NaturalManaRegen = 0;
	float LastManaRegenTime = 0;
	float ManaRegenNotifyInterval = 5.0f;
};
