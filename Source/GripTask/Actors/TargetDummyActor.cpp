// Radek Cehak | Interview Task | Grip Digital


#include "TargetDummyActor.h"

#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "GripTask/GameModes/GripTaskGameplayMode.h"


// Sets default values
ATargetDummyActor::ATargetDummyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
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

// Called every frame
void ATargetDummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
