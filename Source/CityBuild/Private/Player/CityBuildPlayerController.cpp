// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "Player/CityBuildPlayerController.h"
#include "Player/CameraMovementComponent.h"
#include "UI/Elements/BuildingButton.h"

ACityBuildPlayerController::ACityBuildPlayerController()
{	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACityBuildPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Player Controller Started")));
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	FInputModeGameAndUI FInputModeGameAndUI;
	FInputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(FInputModeGameAndUI);

	CityBuildPawn = Cast<ACameraPawnCityBuild>(GetPawn());
	if(CityBuildPawn) CameraMovementComponent = CityBuildPawn->PawnMovementComponent;

	CityBuildHud = Cast<ACityBuildHud>(GetHUD());
	if(!CityBuildHud){
		UE_LOG(LogTemp, Error, TEXT("Error Creating CityBuildHud"));
	}

	CityBuildHud->LoadMainGameMenu();
	CityBuildGameState = Cast<ACityBuildGameState>(GetWorld()->GetGameState());
	
	//Building
	GridManager = GetWorld()->SpawnActor<AGridManager>();
	GridManager->SetPlayerController(this);
	
	CityBuildHud->MainGameHud->BuildingButton1->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding.BP_TestBuilding_C")));
	CityBuildHud->MainGameHud->BuildingButton2->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton3->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Streets/BP_TestStreet.BP_TestStreet_C")));
	CityBuildHud->MainGameHud->BuildingButton4->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton5->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton6->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton7->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton8->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton9->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton10->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton11->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	CityBuildHud->MainGameHud->BuildingButton12->SetBpPath(FSoftClassPath(TEXT("/Game/World/Structures/Buildings/BP_TestBuilding2.BP_TestBuilding2_C")));
	
	//SetPlacementModeEnabled(true, FStringClassReference(TEXT("/Game/World/Buildings/BP_TestBuilding.BP_TestBuilding_C")));
}

void ACityBuildPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraMovementComponent->EdgeScroll();
	GetCityBuildGameState()->UpdateTime();
	if(GetCityBuildHud()->MainGameHud) GetCityBuildHud()->MainGameHud->SetTime(GetCityBuildGameState()->GetTimeString());
	if(GetCityBuildHud()->MainGameHud) GetCityBuildHud()->SetSpareVariableFloat(2, "PlacementModeEnabled", bPlacementModeEnabled);
}

void ACityBuildPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move Forward", this, &ACityBuildPlayerController::MoveForward);
	InputComponent->BindAxis("Move Right", this, &ACityBuildPlayerController::MoveRight);

	InputComponent->BindAction("Speed Modifier", IE_Pressed, this, &ACityBuildPlayerController::IncreaseSpeedModifier);
	InputComponent->BindAction("Speed Modifier", IE_Released, this, &ACityBuildPlayerController::DecreaseSpeedModifier);

	InputComponent->BindAction("Zoom In", IE_Pressed, this, &ACityBuildPlayerController::ZoomIn);
	InputComponent->BindAction("Zoom Out", IE_Pressed, this, &ACityBuildPlayerController::ZoomOut);
	InputComponent->BindAction("Reset Zoom", IE_Pressed, this, &ACityBuildPlayerController::ResetZoom);

	InputComponent->BindAction("Pan Camera Left", IE_Pressed, this, &ACityBuildPlayerController::PanCameraLeft);
	InputComponent->BindAction("Pan Camera Right", IE_Pressed, this, &ACityBuildPlayerController::PanCameraRight);
	InputComponent->BindAction("Pan Reset", IE_Pressed, this, &ACityBuildPlayerController::PanReset);

	InputComponent->BindAction("Developer Info", IE_Pressed, this, &ACityBuildPlayerController::ShowDeveloperInfo);
	InputComponent->BindAction("Pause Menu", IE_Pressed, this, &ACityBuildPlayerController::OpenPauseMenu);

	InputComponent->BindAction("Mouse Left Click", IE_Pressed, this, &ACityBuildPlayerController::HandleLeftClick);
	InputComponent->BindAction("Mouse Right Click", IE_Pressed, this, &ACityBuildPlayerController::HandleRightClick);
}

bool ACityBuildPlayerController::SetPause(const bool bPause, FCanUnpause CanUnpauseDelegate)
{
	CameraMovementComponent->CameraOwner->AddActorLocalOffset(FVector(0.0f, 0.0f, 0.0f), true);
	return Super::SetPause(bPause);
}

void ACityBuildPlayerController::MoveForward(const float AxisValueX)
{
	CameraMovementComponent->BasicMovementControl(AxisValueX, 0);
}

void ACityBuildPlayerController::MoveRight(const float AxisValueY)
{
	CameraMovementComponent->BasicMovementControl(0, AxisValueY);
}

void ACityBuildPlayerController::IncreaseSpeedModifier()
{
	CameraMovementComponent->SetMovementSpeedModifierActive(true);
}

void ACityBuildPlayerController::DecreaseSpeedModifier()
{
	CameraMovementComponent->SetMovementSpeedModifierActive(false);
}

void ACityBuildPlayerController::ZoomIn()
{
	CameraMovementComponent->ZoomIn();
}

void ACityBuildPlayerController::ZoomOut()
{
	CameraMovementComponent->ZoomOut();
}

void ACityBuildPlayerController::ResetZoom()
{
	CameraMovementComponent->DefaultZoom();
}

void ACityBuildPlayerController::PanCameraLeft()
{
	CameraMovementComponent->PanCamera(45.0);
}

void ACityBuildPlayerController::PanCameraRight()
{
	CameraMovementComponent->PanCamera(-45.0);
}

void ACityBuildPlayerController::PanReset()
{
	CameraMovementComponent->ResetPan();
}

void ACityBuildPlayerController::ShowDeveloperInfo()
{
	CityBuildHud->LoadDeveloperInfo();
}

void ACityBuildPlayerController::OpenPauseMenu()
{
	if(!CityBuildGameState->IsPauseMenuOpen())
	{
		CityBuildHud->LoadPauseMenu();	
	}else
	{
		if(CityBuildHud->Pause) CityBuildHud->Pause->Continue();
	}
}

void ACityBuildPlayerController::HandleLeftClick()
{
	if(bPlacementModeEnabled) SpawnBuilding();
}

void ACityBuildPlayerController::HandleRightClick()
{
	if(bPlacementModeEnabled)
	{
		SetPlacementModeEnabled(false, nullptr);
		CityBuildHud->MainGameHud->SetActiveBuildButton(CityBuildHud->MainGameHud->ActiveBuildButton, false);
	}
}


//Class Declarations
ACityBuildHud* ACityBuildPlayerController::GetCityBuildHud() const
{
	return CityBuildHud;
}

ACameraPawnCityBuild* ACityBuildPlayerController::GetCityBuildPawn() const
{
	return CityBuildPawn;
}

UCameraMovementComponent* ACityBuildPlayerController::GetCameraMovementComponent() const
{
	return CameraMovementComponent;
}

ACityBuildGameState* ACityBuildPlayerController::GetCityBuildGameState() const
{
	return CityBuildGameState;
}

//Build
void ACityBuildPlayerController::SetPlacementModeEnabled(const bool IsEnabled, const TSubclassOf<class AMasterStructureAsset> BuildingClass)
{
	if(PlaceableActor)	PlaceableActor->Destroy();
	bPlacementModeEnabled = IsEnabled;
	TempBuildingClass = BuildingClass;
	if(IsEnabled)
	{
		GridManager->ActivateGrid(true);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		PlaceableActor = GetWorld()->SpawnActor<AMasterStructureAsset>(BuildingClass, FVector(0.0f, 0.0f, -1000000.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
		
		PlaceableActor->SetBuildingMode(true);
	}else
	{
		if(PlaceableActor)	PlaceableActor->Destroy();
		GridManager->ActivateGrid(false);
	}
}

void ACityBuildPlayerController::UpdatePlacement(const AGridCell* Cell) const
{
	if(Cell && PlaceableActor)
	{
		float XLoc = Cell->GetActorLocation().X;
		float YLoc = Cell->GetActorLocation().Y;

		FVector Origin, BoxExtent;
		PlaceableActor->GetActorBounds(false, Origin, BoxExtent);

		const int32 WorldGridSize = GridManager->GetWorldGridSize();
			
		if(BoxExtent.X * 2 > WorldGridSize && static_cast<int32>(BoxExtent.X * 2 / WorldGridSize) % 2 == 0)
			XLoc = XLoc - fabs(static_cast<int32>(XLoc) % WorldGridSize);
		if(BoxExtent.Y * 2 > WorldGridSize && static_cast<int32>(BoxExtent.Y * 2 / WorldGridSize) % 2 == 0)
			YLoc = YLoc + fabs(static_cast<int32>(YLoc) % WorldGridSize);
		
		PlaceableActor->SetActorLocation(FVector(XLoc, YLoc, Cell->GetActorLocation().Z + BoxExtent.Z));
		//GridManager->MarkNeighbours(Cell);
	}
}

void ACityBuildPlayerController::SpawnBuilding()
{
	if(PlaceableActor->GetIsPlacementValid())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FVector Location = PlaceableActor->GetActorLocation();
		const FRotator Rotation = PlaceableActor->GetActorRotation();
		PlaceableActor->SetBuildingMode(false);
		PlaceableActor = GetWorld()->SpawnActor<AMasterStructureAsset>(TempBuildingClass, Location, Rotation, SpawnInfo);
		
		//GridManager->MakeCellsInvisible(GridManager->FindCellsBelowActor(PlaceableActor)); @Todo: GridManager->FindCellsBelowActor( *Actor* )
		
		SetPlacementModeEnabled(true, TempBuildingClass);
	}
}

AGridManager* ACityBuildPlayerController::GetGridManager() const
{
	return GridManager;
}

bool ACityBuildPlayerController::GetPlacementModeEnabled() const
{
	return bPlacementModeEnabled;
}


