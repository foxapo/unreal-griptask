// Radek Cehak | Interview Task | Grip Digital


#include "TextWidgetBase.h"


void UTextWidgetBase::SetText(FText NewText)
{
	if (TextBlock)
	{
		TextBlock->SetText(NewText);
	}
}
