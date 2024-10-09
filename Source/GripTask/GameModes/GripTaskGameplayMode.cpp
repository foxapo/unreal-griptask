// Radek Cehak | Interview Task | Grip Digital

#include "GripTaskGameplayMode.h"
#include "Engine/DataTable.h"
#include "GripTask/Data/FCharacterStats.h"

void AGripTaskGameplayMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay BeginPlay"));
	}

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}

FCharacterStats* AGripTaskGameplayMode::GetCharacterStats(FName RowName) const
{
	if (CharacterStatsDataTable)
	{
		static const FString ContextString(TEXT("Character Stats Context"));
		return CharacterStatsDataTable->FindRow<FCharacterStats>(RowName, ContextString);
	}
	return nullptr;
}
