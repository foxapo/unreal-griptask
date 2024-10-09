#include "UTargetInterface.h"
#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"

bool ITargetInterface::IsTarget() const
{
	// Provide a default implementation or leave it empty if it should be overridden by derived classes
	return false;
}

UAttributeComponent* ITargetInterface::GetAttributeComponent()
{
	// Provide a default implementation or leave it empty if it should be overridden by derived classes
	return nullptr;
}

UTargetComponent* ITargetInterface::GetActorTargetComponent()
{
	// Provide a default implementation or leave it empty if it should be overridden by derived classes
	return nullptr;
}