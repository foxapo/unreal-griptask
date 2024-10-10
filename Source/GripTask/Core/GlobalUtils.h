// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"

class AGameplayHUD;
/*
 *	Helper functions for global access to various objects
 */
namespace GlobalUtils
{
	AGameplayHUD* GetGameplayHUD(const UWorld* World);
}
