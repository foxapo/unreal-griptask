// Radek Cehak | Interview Task | Grip Digital


#include "MinimapWidget.h"
#include "Components/Image.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (MapBackgroundColor)
	{
		MapBackgroundColor->SetColorAndOpacity(MapColor);
	}
}
