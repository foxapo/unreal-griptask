// Radek Cehak | Interview Task | Grip Digital


#include "InventoryItem.h"
#include "Components/Image.h"

void UInventoryItem::Unset() const
{
	ItemImage->SetVisibility(ESlateVisibility::Hidden);
}
