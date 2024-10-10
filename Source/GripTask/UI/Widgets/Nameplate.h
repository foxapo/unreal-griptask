// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GripTask/Components/AttributeComponent.h"
#include "Nameplate.generated.h"


class ITargetInterface;

UCLASS(Abstract)
class GRIPTASK_API UNameplate : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealth(float Health);
	UFUNCTION()
	void UpdateMana(float Mana);
	UFUNCTION()
	void UpdateName(const FString& String);
	UFUNCTION()
	void UpdateLevel(int8 INT8);
	UFUNCTION()
	void InitTarget(TScriptInterface<ITargetInterface> Target);
	UFUNCTION()
	void Select();
	UFUNCTION()
	void Deselect();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealth;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealth;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Level;
	UPROPERTY(meta = (BindWidget))
	class UImage* SelectionFrame;
	UPROPERTY()
	TScriptInterface<ITargetInterface> Target;
};
