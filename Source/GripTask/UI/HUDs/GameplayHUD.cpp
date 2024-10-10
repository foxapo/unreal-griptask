// Radek Cehak | Interview Task | Grip Digital


#include "GameplayHUD.h"
#include "GripTask/UI/GameplayLayoutWidget.h"

void AGameplayHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GameplayLayoutWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("GameplayLayoutWidgetClass is not set in the GameplayHUD"));
		return;
	}

	GameplayLayoutWidget = CreateWidget<UGameplayLayoutWidget>(GetWorld(), GameplayLayoutWidgetClass);
	if (!GameplayLayoutWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("GameplayLayoutWidget is nullptr"));
		return;
	}

	GameplayLayoutWidget->AddToViewport();
}

void AGameplayHUD::ToggleQuestLog()
{
	bQuestMenuVisible = !bQuestMenuVisible;
	if (GameplayLayoutWidget)
	{
		GameplayLayoutWidget->SetQuestMenu(bQuestMenuVisible);
	}
}
