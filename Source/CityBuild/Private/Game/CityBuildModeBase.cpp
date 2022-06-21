// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "Game/CityBuildGameModeBase.h"
#include "Player/CityBuildPlayerController.h"
#include "Player/CityBuildPlayerState.h"

ACityBuildGameModeBase::ACityBuildGameModeBase()
{
	DefaultPawnClass = ACameraPawnCityBuild::StaticClass();
	PlayerControllerClass = ACityBuildPlayerController::StaticClass();
	HUDClass = ACityBuildHud::StaticClass();
	GameStateClass = ACityBuildGameState::StaticClass();
	PlayerStateClass = ACityBuildPlayerState::StaticClass();
}

void ACityBuildGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("TopDown GameMode Started")));
}



