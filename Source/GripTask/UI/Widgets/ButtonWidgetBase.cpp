// Radek Cehak | Interview Task | Grip Digital

#include "ButtonWidgetBase.h"


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
	}
}

void UButtonWidgetBase::OnButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Button clicked"));
	}
}

