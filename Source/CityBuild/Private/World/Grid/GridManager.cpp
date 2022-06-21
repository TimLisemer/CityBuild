// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "World/Grid/GridManager.h"
#include "Player/CityBuildPlayerController.h"
#include "World/Grid/GridCell.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	static ConstructorHelpers::FObjectFinder<UMaterial> GMaterial(TEXT("Material'/Game/Material/Test/GreenMaterial.GreenMaterial'"));
	if(GMaterial.Object) ValidMaterial = GMaterial.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> RMaterial(TEXT("Material'/Game/Material/Test/RedMaterial.RedMaterial'"));
	if(RMaterial.Object) InvalidMaterial = RMaterial.Object;
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	SetupMaterial();
}

void AGridManager::SetupMaterial()
{
	DefaultMaterial_Dynamic = UMaterialInstanceDynamic::Create(DefaultMaterial, this);
	ValidMaterial_Dynamic = UMaterialInstanceDynamic::Create(ValidMaterial, this);
	InvalidMaterial_Dynamic = UMaterialInstanceDynamic::Create(InvalidMaterial, this);
	
	InvisibleMaterial_Dynamic = UMaterialInstanceDynamic::Create(DefaultMaterial, this);
	InvisibleMaterial_Dynamic->SetScalarParameterValue("Opacity", 0.0f);
}

void AGridManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(GetWorld())
	{
		FVector MouseLocation, MouseDirection;
		PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

		FVector StartLocation = MouseLocation;
		FVector EndLocation = MouseDirection * 100000000 + MouseLocation;

		FHitResult Hit;
			
		GetWorld()->LineTraceSingleByChannel(
			Hit,
			StartLocation,
			EndLocation,
			ECC_GameTraceChannel1,
			FCollisionQueryParams(),
			FCollisionResponseParams::DefaultResponseParam
			);

		if(AGridCell* HitActor = dynamic_cast<AGridCell*>(Hit.GetActor())) {
			if(!HitActor->IsCellSelected())
			{
				HitActor->SetCellSelected(true);
				PlayerController->UpdatePlacement(HitActor);

				for(int32 i = 0; i < GridSize; i++)	//Y Loop
					{
					for(int32 d = 0; d < GridSize; d++)	//X Loop
						{
						AGridCell* Cell = GridArray[i].XGridArray[d];
						if(Cell != HitActor && Cell->IsCellSelected()) Cell->SetCellSelected(false);
						}
					}
			}
		}
	}
}

void AGridManager::SetPlayerController(ACityBuildPlayerController* Pc)
{
	PlayerController = Pc;
	PopulateGrid();
}

void AGridManager::PopulateGrid()
{
	const float GridDistance = GridSize*WorldGridSize/2;

	//Vermutlich entfernen um Cell nicht in der mitte zu haben
	const float GridCenterCell = WorldGridSize/2;

	const float WorldOffset = GridDistance-GridCenterCell;

	for(int32 i = 0; i < GridSize; i++)	//Y Loop
	{
		GridArray.Add(FGridArray());
		for(int32 d = 0; d < GridSize; d++)	//X Loop
		{
			FVector Location = FVector(i*WorldGridSize-WorldOffset, d*WorldGridSize-WorldOffset, 100.0f);

			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FSoftClassPath BpPath = FSoftClassPath(TEXT("/Game/World/Grid/BP_GridCell.BP_GridCell_C"));
			
			const TSubclassOf<class AGridCell> GridBP = BpPath.TryLoadClass<AGridCell>();
			AGridCell* Cell = GetWorld()->SpawnActor<AGridCell>(GridBP, Location, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
			if(PlayerController) Cell->SetPlayerController(PlayerController);
			GridArray[i].XGridArray.Add(Cell);
			Cell->SetLocation(FVector2D(Location[0], Location[1]));
			Cell->SetPosition(i, d);
		}
	}
}

void AGridManager::ActivateGrid(const bool BuildModeActive)
{
	SetActorTickEnabled(BuildModeActive);

	for(int32 i = 0; i < GridSize; i++)	//Y Loop
		{
		for(int32 d = 0; d < GridSize; d++)	//X Loop
			{
			AGridCell* Cell = GridArray[i].XGridArray[d];
			Cell->SetCellActive(BuildModeActive);
			}
		}
}

UMaterialInstanceDynamic* AGridManager::GetDefaultMaterial_Dynamic() const
{
	return DefaultMaterial_Dynamic;
}

UMaterialInstanceDynamic* AGridManager::GetValidMaterial_Dynamic() const
{
	return ValidMaterial_Dynamic;
}

UMaterialInstanceDynamic* AGridManager::GetInvalidMaterial_Dynamic() const
{
	return InvalidMaterial_Dynamic;
}

UMaterialInstanceDynamic* AGridManager::GetInvisibleMaterial_Dynamic() const
{
	return InvisibleMaterial_Dynamic;
}

float AGridManager::GetWorldGridSize() const
{
	return WorldGridSize;
}

void AGridManager::ClearCells()
{
	for(int32 i = 0; i < GridSize; i++)	//Y Loop
	{
		for(int32 d = 0; d < GridSize; d++)	//X Loop
		{
			const AGridCell* Cell = GridArray[i].XGridArray[d];
			Cell->ChangeMaterial(GetInvisibleMaterial_Dynamic());
		}
	}
}

AGridCell* AGridManager::GetNorthernNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI + 1 >= GridSize) return nullptr;
	return GridArray[StartI + 1].XGridArray[StartD];
}

AGridCell* AGridManager::GetSouthernNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI - 1 < 0) return nullptr;
	return GridArray[StartI - 1].XGridArray[StartD];
}

AGridCell* AGridManager::GetEasternNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartD + 1 >= GridSize) return nullptr;
	return GridArray[StartI].XGridArray[StartD + 1];
}

AGridCell* AGridManager::GetWesternNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartD - 1 < 0) return nullptr;
	return GridArray[StartI].XGridArray[StartD - 1];
}

AGridCell* AGridManager::GetNorthEastNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI + 1 >= GridSize) return nullptr;
	if(StartD + 1 >= GridSize) return nullptr;
	return GridArray[StartI + 1].XGridArray[StartD + 1];
}

AGridCell* AGridManager::GetNorthWestNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI + 1 >= GridSize) return nullptr;
	if(StartD - 1 < 0) return nullptr;
	return GridArray[StartI + 1].XGridArray[StartD - 1];
}

AGridCell* AGridManager::GetSouthEastNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI - 1 < 0) return nullptr;
	if(StartD - 1 < 0) return nullptr;
	return GridArray[StartI - 1].XGridArray[StartD - 1];
}

AGridCell* AGridManager::GetSouthWestNeighbour(const AGridCell* StartCell)
{
	const int32 StartI = StartCell->GetPosI(), StartD = StartCell->GetPosD();
	if(StartI - 1 < 0) return nullptr;
	if(StartD + 1 >= GridSize) return nullptr;
	return GridArray[StartI - 1].XGridArray[StartD + 1];
}

void AGridManager::MakeCellsInvisible(TArray<AGridCell*> Cells)
{
	for(const AGridCell* Cell : Cells)
	{
		Cell->SetVisibility(false);
	}
}

