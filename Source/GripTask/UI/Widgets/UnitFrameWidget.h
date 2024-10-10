// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitFrameWidget.generated.h"

class UImage;
class UTextBlock;
class ITargetInterface;
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
	void Toggle(bool State);
	void UnsubscribeTarget();
	void SubscribeTarget();
	void InitTarget(TScriptInterface<ITargetInterface> Target);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;
	UPROPERTY(meta = (BindWidget))
	UImage* PlayerPortrait;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelValue;

private:
	TScriptInterface<ITargetInterface> CurrentTarget;

	UFUNCTION()
	void UpdateHealth(float Health);
	UFUNCTION()
	void UpdateMana(float Mana);
	UFUNCTION()
	void UpdateName(const FString& Name) const;
	UFUNCTION()
	void UpdatePortrait(UTexture2D* Portrait) const;
	UFUNCTION()
	void UpdateLevel(int8 Level) const;


	// Interpolation of the bar change
	float CurrentHealthPercent = 0;
	float TargetHealthPercent = 0;
	float CurrentManaPercent = 0;
	float TargetManaPercent = 0;
	float InterpolationSpeed = 5.0f;

	bool bIsPlayer = false;
};
