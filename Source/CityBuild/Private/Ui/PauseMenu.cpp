// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "UI/PauseMenu.h"
// ReSharper disable once CppUnusedIncludeDirective --- https://forums.unrealengine.com/t/unresolved-external-symbol-fslatecolor-including-fix/141172
#include "Styling/SlateColor.h"
#include "Components/Button.h"
#include "Player/CityBuildPlayerController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/KismetSystemLibrary.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if(BContinue && BMainMenu && BExit)
	{
		BContinue->OnClicked.AddDynamic(this, &UPauseMenu::Continue);
		BMainMenu->OnClicked.AddDynamic(this, &UPauseMenu::MainMenu);
		BExit->OnClicked.AddDynamic(this, &UPauseMenu::Exit);
		Cast<ACityBuildGameState>(GetWorld()->GetGameState())->SetOpenedPauseMenu(true);
	} else UE_LOG(LogTemp, Error, TEXT("Error while loading Pause Menu Buttons"));
}

void UPauseMenu::Continue()
{
	Cast<ACityBuildGameState>(GetWorld()->GetGameState())->SetOpenedPauseMenu(false);
	Cast<ACityBuildPlayerController>(GetPlayerContext().GetPlayerController())->SetPause(false);
	RemoveFromViewport();
}

void UPauseMenu::MainMenu()
{
	RemoveFromViewport();
	Cast<ACityBuildGameState>(GetWorld()->GetGameState())->SetOpenedPauseMenu(false);
	//@Todo Add Main Menu and Open From Here
}

void UPauseMenu::Exit()
{
	RemoveFromViewport();
	Cast<ACityBuildGameState>(GetWorld()->GetGameState())->SetOpenedPauseMenu(false);
	UKismetSystemLibrary::QuitGame(GetWorld(), GetPlayerContext().GetPlayerController(), EQuitPreference::Quit, false);
}

