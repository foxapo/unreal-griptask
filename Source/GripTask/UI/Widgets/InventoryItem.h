// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "DraggableWidgetBase.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class GRIPTASK_API UInventoryItem : public UDraggableWidgetBase
{
	GENERATED_BODY()

public:
	void Unset() const;

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
};
