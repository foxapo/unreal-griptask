// Radek Cehak | Interview Task | Grip Digital

#include "TargetComponent.h"

#include "AttributeComponent.h"
#include "GripTask/Characters/GripTaskCharacter.h"

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

void UTargetComponent::DoDamage() const
{
	if (Target)
	{
		const int RandomDamage = FMath::RandRange(5, 35);
		Target->GetAttributeComponent()->ApplyDamage(RandomDamage);
	}
}

void UTargetComponent::DoHeal() const
{
	if (Target)
	{
		const int RandomHeal = FMath::RandRange(5, 35);
		Target->GetAttributeComponent()->ApplyHeal(RandomHeal);
	}
}
