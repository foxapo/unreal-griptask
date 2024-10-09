// Radek Cehak | Interview Task | Grip Digital

#include "ButtonWidgetBase.h"
#include "GripTask/Core/DebugMacros.h"

void UButtonWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetButtonClickHandler();
}

void UButtonWidgetBase::SetButtonClickHandler()
{
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UButtonWidgetBase::OnButtonClicked);
		Button->OnHovered.AddDynamic(this, &UButtonWidgetBase::OnButtonHovered);
	}
}

void UButtonWidgetBase::OnButtonClicked()
{
	DEBUG_PRINT("Button clicked");
}

void UButtonWidgetBase::OnButtonHovered()
{
	DEBUG_PRINT("Button hovered");
}
