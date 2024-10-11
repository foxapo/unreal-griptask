// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "DraggableWidgetBase.h"
#include "InventoryMenu.generated.h"

class UInventoryItem;
/**
 * 
 */
UCLASS()
class GRIPTASK_API UInventoryMenu : public UDraggableWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* InventoryWrapBox;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<class UInventoryItem> InventoryItemClass;

};
