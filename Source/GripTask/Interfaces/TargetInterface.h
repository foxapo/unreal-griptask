#pragma once

#include "UObject/Interface.h"
#include "CoreMinimal.h"
#include "TargetInterface.generated.h"

class UTargetComponent;
class UAttributeComponent;

UINTERFACE(MinimalAPI, Blueprintable)
class UTargetInterface : public UInterface
{
	GENERATED_BODY()
};

class ITargetInterface
{
	GENERATED_BODY()

public:
	virtual bool IsTarget() = 0;
	virtual UAttributeComponent* GetAttributeComponent() = 0;
	virtual UTargetComponent* GetActorTargetComponent() = 0;
};
