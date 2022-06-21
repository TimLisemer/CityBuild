// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "World/Grid/GridCell.h"
#include "Player/CityBuildPlayerController.h"

// Sets default values
AGridCell::AGridCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();

	TScriptDelegate <FWeakObjectPtr> BeginCursorOver1;
	BeginCursorOver1.BindUFunction(this, "BeginCursorOver");
	OnBeginCursorOver.Add(BeginCursorOver1);

	TScriptDelegate <FWeakObjectPtr> EndCursorOver1;
	EndCursorOver1.BindUFunction(this, "EndCursorOver");
	OnEndCursorOver.Add(EndCursorOver1);

	SetCellActive(false);
}

void AGridCell::SetPlayerController(ACityBuildPlayerController* Pc)
{
	PlayerController = Pc;
}

void AGridCell::SetCellActive(const bool Active)
{
	bActive = Active;
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	for(UStaticMeshComponent* Mesh : Components)
	{
		Mesh->SetVisibility(Active,true);
	}
}

void AGridCell::ChangeMaterial(UMaterialInterface* Material) const
{
	if(!this) return;
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	UStaticMeshComponent* Mesh = Components[0];
	Mesh->SetMaterial(0, Material);
}

void AGridCell::SetCellSelected(const bool Selected)
{
	bSelected = Selected;
}

bool AGridCell::IsCellSelected() const
{
	return bSelected;
}

/* Todo: Delete
void AGridCell::BeginCursorOver() const
{
	if(PlayerController && bActive)
	{
		PlayerController->UpdatePlacement(const_cast<AGridCell*>(this), true);
	}
}
void AGridCell::EndCursorOver() const
{
	if(PlayerController && bActive)
	{
		PlayerController->UpdatePlacement(const_cast<AGridCell*>(this), false);
	}
}*/

int32 AGridCell::GetPosI() const
{
	return PosI;
}

int32 AGridCell::GetPosD() const
{
	return PosD;
}

void AGridCell::SetPosition(const int32 I, const int32 D)
{
	PosI = I;
	PosD = D;
}

FVector2D AGridCell::GetLocation() const
{
	return Location;
}

void AGridCell::SetLocation(const FVector2D Loc)
{
	Location = Loc;
}

void AGridCell::SetVisibility(const bool bVisibility) const
{
	if(PlayerController)
	{
		const AGridManager* GridManager = PlayerController->GetGridManager();
	
		if(bVisibility && GridManager)
		{
			//ChangeMaterial(GridManager->GetDefaultMaterial_Dynamic());
			ChangeMaterial(GridManager->GetInvalidMaterial_Dynamic());
		}else
		{
			ChangeMaterial(GridManager->GetValidMaterial_Dynamic());
		}
	}
}

