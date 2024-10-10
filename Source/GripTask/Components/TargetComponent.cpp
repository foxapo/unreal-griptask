// Radek Cehak | Interview Task | Grip Digital

#include "TargetComponent.h"

#include "GripTask/Characters/GripTaskCharacter.h"
#include "GripTask/Core/DebugMacros.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetComponent::SetPlayerController(APlayerController* Controller)
{
	PlayerController = Controller;
	bIsPlayer = true;
}

void UTargetComponent::SetTarget(UObject* Object)
{
	if (ITargetInterface* TargetInterface = Cast<ITargetInterface>(Object))
	{
		if (Target.GetInterface() == TargetInterface)
		{
			return;
		}

		if (Target)
		{
			UnsetTarget();
		}

		Target.SetObject(Object);
		Target.SetInterface(TargetInterface);
		Target->GetActorTargetComponent()->OnSelected.Broadcast();
		OnTargetChanged.Broadcast(true);
	}
}

void UTargetComponent::UnsetTarget()
{
	if (Target != nullptr)
	{
		Target->GetActorTargetComponent()->OnDeselected.Broadcast();
		Target = nullptr;
		OnTargetChanged.Broadcast(false);
	}
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	OnTargetChanged.Broadcast(false);
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
				if (HitResult.GetActor() == GetOwner())
				{
					// DO NOTHING WHEN CLICK ON PLAYER
					return;
				}

				SetTarget(HitResult.GetActor());
				return;
			}
		}
	}

	UnsetTarget();
}
