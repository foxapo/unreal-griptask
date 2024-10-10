// Radek Cehak | Interview Task | Grip Digital


#include "GlobalUtils.h"
#include "GripTask/UI/HUDs/GameplayHUD.h"

AGameplayHUD* GlobalUtils::GetGameplayHUD(const UWorld* World)
{
	if (const APlayerController* PlayerController = World->GetFirstPlayerController())
	{
		return Cast<AGameplayHUD>(PlayerController->GetHUD());
	}
	return nullptr;
}
