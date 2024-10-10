// Radek Cehak | Interview Task | Grip Digital


#include "TargetDummyActor.h"

#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "GripTask/GameModes/GripTaskGameplayMode.h"

ATargetDummyActor::ATargetDummyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));
}

bool ATargetDummyActor::IsTarget()
{
	return true;
}

UTargetComponent* ATargetDummyActor::GetActorTargetComponent()
{
	return TargetComponent;
}

UAttributeComponent* ATargetDummyActor::GetAttributeComponent()
{
	return AttributeComponent;
}

void ATargetDummyActor::BeginPlay()
{
	Super::BeginPlay();
	if (!AttributeComponent)
	{
		DEBUG_PRINT("AttributeComponent not set");
	}
	else
	{
		SetupCharacterStats(AttributeComponent->GetCharacterStatsId());
	}
}

void ATargetDummyActor::SetupCharacterStats(FName Id)
{
	if (const AGripTaskGameplayMode* GameMode = Cast<AGripTaskGameplayMode>(GetWorld()->GetAuthGameMode()))
	{
		if (FCharacterStats* Stats = GameMode->GetCharacterStats(Id))
		{
			AttributeComponent->SetBaseStats(Stats);
		}
	}
}

void ATargetDummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
