// Radek Cehak | Interview Task | Grip Digital


#include "GripTaskGameplayMode.h"

void AGripTaskGameplayMode::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gameplay BeginPlay"));
	}
}
