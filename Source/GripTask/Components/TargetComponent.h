// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "TargetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRIPTASK_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();
	void SetPlayerController(APlayerController* NewController);
	void SetTarget(UObject* NewObject);
	void UnsetTarget();
	void RaycastTargetInterface();
	TScriptInterface<ITargetInterface> GetCurrentTarget() const { return Target; }

	// * EVENTS * //

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChanged, bool, bIsTarget);

	UPROPERTY(BlueprintAssignable, Category="Target")
	FOnTargetChanged OnTargetChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelected);

	UPROPERTY(BlueprintAssignable, Category="Target")
	FOnSelected OnSelected;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeselected);

	UPROPERTY(BlueprintAssignable, Category="Target")
	FOnDeselected OnDeselected;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLostFocus);

	UPROPERTY(BlueprintAssignable, Category="Target")
	FOnLostFocus OnLostFocus;


protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<ITargetInterface> Target;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer = false;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	bool bLostFocus = false;
};
