// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitFrameWidget.generated.h"

class UAttributeComponent;
class UProgressBar;
class AGripTaskCharacter;
/**
 * 
 */
UCLASS()
class GRIPTASK_API UUnitFrameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void InitPlayer(AGripTaskCharacter* Player);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;

private:
	AGripTaskCharacter* Character;

	UFUNCTION()
	void UpdateHealth(float Health);
	UFUNCTION()
	void UpdateMana(float Mana);

	// Interpolation of the bar change
	float CurrentHealthPercent = 0;
	float TargetHealthPercent = 0;
	float CurrentManaPercent = 0;
	float TargetManaPercent = 0;
	float InterpolationSpeed = 5.0f;
};
