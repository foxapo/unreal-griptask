// Radek Cehak | Interview Task | Grip Digital


#include "InventoryMenu.h"
#include "InventoryItem.h"
#include "Components/WrapBox.h"


void UInventoryMenu::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 30; i++)
	{
		UInventoryItem* ItemWidget = CreateWidget<UInventoryItem>(GetWorld(), InventoryItemClass);
		// Random chance 50% to set the item
		if (FMath::RandRange(0, 1) == 1)
		{
			ItemWidget->Unset();
		}

		InventoryWrapBox->AddChildToWrapBox(ItemWidget);
	}
}
