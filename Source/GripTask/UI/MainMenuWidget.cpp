// Radek Cehak | Interview Task | Grip Digital


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
	}
}

void UMainMenuWidget::OnStartButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Start button clicked"));
	}

	// Load Level by Name
	UGameplayStatics::OpenLevel(GetWorld(), "Gameplay");
}

void UMainMenuWidget::OnExitButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit button clicked"));
	}
}
