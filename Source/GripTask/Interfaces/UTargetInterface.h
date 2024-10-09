#pragma once

#include "UObject/Interface.h"
#include "CoreMinimal.h"
#include "UTargetInterface.generated.h"

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
	virtual bool IsTarget() const;
	virtual UAttributeComponent* GetAttributeComponent();
	virtual UTargetComponent* GetActorTargetComponent();
};
