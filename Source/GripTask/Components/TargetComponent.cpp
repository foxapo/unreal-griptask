// Radek Cehak | Interview Task | Grip Digital

#include "TargetComponent.h"

#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Core/DebugMacros.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetComponent::SetPlayerController(APlayerController* Controller)
{
	PlayerController = Controller;
	bIsPlayer = true;
}

void UTargetComponent::SetTarget(TScriptInterface<ITargetInterface> NewTarget)
{
	Target = NewTarget;
}

void UTargetComponent::LeftMouseClicked()
{
	RaycastTargetInterface();
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	NotifyTargetChange(false);
}

void UTargetComponent::NotifyTargetChange(bool bIsTarget)
{
	DEBUG_PRINT("Target changed");
	OnTargetChanged.Broadcast(bIsTarget);
}

void UTargetComponent::RaycastTargetInterface()
{
	if (!bIsPlayer)
	{
		return;
	}

	if (PlayerController.IsValid())
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, HitResult);
		if (HitResult.bBlockingHit)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UTargetInterface::StaticClass()))
			{
				if (HitResult.GetActor() == PlayerController->GetPawn())
				{
					return;
				}

				if (ITargetInterface* TargetInterface = Cast<ITargetInterface>(HitResult.GetActor()))
				{
					if (Target.GetInterface() != TargetInterface)
					{
						Target.SetObject(HitResult.GetActor());
						Target.SetInterface(TargetInterface);
						NotifyTargetChange(true);
					}
					return;
				}
			}
		}
	}

	Target = nullptr;
	NotifyTargetChange(false);
}

// void UTargetActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
//                                           FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// 	if (!bIsPlayer)
// 	{
// 		return;
// 	}
//
// 	if (RaycastTargetInterface()) return;
//
// 	if (Target != nullptr && !bLostFocus)
// 	{
// 		Target = nullptr;
// 		NotifyTargetChange();
// 		bLostFocus = true;
// 	}
// }
