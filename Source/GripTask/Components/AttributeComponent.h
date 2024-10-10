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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetBaseStats(const FCharacterStats* Stats);
	void RegenerateMana(float DeltaTime);
	void ConsumeMana(float Value);
	FName GetId() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, Mana);

	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Attributes")
	FOnManaChanged OnManaChanged;

	FORCEINLINE FCharacterStats GetBaseStats() const { return BaseStats; }
	FORCEINLINE FName GetCharacterStatsId() const { return CharacterStatsId; }
	FORCEINLINE float GetHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMana() const { return CurrentMana; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetMaxMana() const { return MaxMana; }
	FORCEINLINE float GetNaturalManaRegen() const { return NaturalManaRegen; }

protected:
	virtual void BeginPlay() override;
	void NotifyHealthChanged() const;
	void NotifyManaChanged() const;

	UPROPERTY(EditAnywhere, Category="Attributes")
	FName CharacterStatsId;

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
