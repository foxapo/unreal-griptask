// Radek Cehak | Interview Task | Grip Digital


#include "MainMenuHUD.h"
#include "GripTask/UI/MainMenuWidget.h"


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}

}
