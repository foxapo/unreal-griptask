// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GripTask/Interfaces/UTargetInterface.h"
#include "TargetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRIPTASK_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();
	void SetPlayerController(APlayerController* NewController);
	void SetTarget(TScriptInterface<ITargetInterface> NewTarget);
	void LeftMouseClicked();
	TScriptInterface<ITargetInterface> GetCurrentTarget() const { return Target; }
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChanged, bool, bIsTarget);
	UPROPERTY(BlueprintAssignable, Category="Target")
	FOnTargetChanged OnTargetChanged;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyTargetChange(bool bIsTarget);
	void RaycastTargetInterface();

private:
	TWeakObjectPtr<APlayerController> PlayerController;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<ITargetInterface> Target;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	bool bIsPlayer = false;
	UPROPERTY(BlueprintReadOnly, Category="Target", meta = (AllowPrivateAccess = "true"))
	bool bLostFocus = false;
};
