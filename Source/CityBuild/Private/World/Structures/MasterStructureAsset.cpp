// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "World/Structures/MasterStructureAsset.h"
#include "Player/CityBuildPlayerController.h"
#include "World/Grid/GridManager.h"

AMasterStructureAsset::AMasterStructureAsset()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetBuildingMode(false);
}

// Called when the game starts or when spawned
void AMasterStructureAsset::BeginPlay()
{
	Super::BeginPlay();

	TScriptDelegate <FWeakObjectPtr> MouseClicked;
	MouseClicked.BindUFunction(this, "MouseClicked");
	OnClicked.Add(MouseClicked);
	
	TScriptDelegate <FWeakObjectPtr> BeginCursorOver;
	BeginCursorOver.BindUFunction(this, "BeginCursorOver");
	OnBeginCursorOver.Add(BeginCursorOver);

	TScriptDelegate <FWeakObjectPtr> EndCursorOver;
	EndCursorOver.BindUFunction(this, "EndCursorOver");
	OnEndCursorOver.Add(EndCursorOver);

	//Build Mode Events
	TScriptDelegate <FWeakObjectPtr> ActorBeginOverlap;
	ActorBeginOverlap.BindUFunction(this, "OnOverlapStatusChanged");
	OnActorBeginOverlap.Add(ActorBeginOverlap);

	TScriptDelegate <FWeakObjectPtr> ActorEndOverlap;
	ActorEndOverlap.BindUFunction(this, "OnOverlapStatusChanged");
	OnActorEndOverlap.Add(ActorEndOverlap);
}

void AMasterStructureAsset::MouseClicked()
{
	if(!GetBuildingMode())
	{
		BIsClicked = true;
		UE_LOG(LogTemp, Error, TEXT("MouseClicked"));
		
		const ACityBuildPlayerController* PlayerController = Cast<ACityBuildPlayerController>(GetWorld()->GetFirstPlayerController());
		ACityBuildHud* CityBuildHud = PlayerController->GetCityBuildHud();
		CityBuildHud->LoadBuildingWidget(this);

		UE_LOG(LogTemp, Error, TEXT("MouseClicked Success"));
	}
}

void AMasterStructureAsset::BeginCursorOver() const
{
	if(!GetBuildingMode())
	{
		TArray<UStaticMeshComponent*> Components;
		GetComponents<UStaticMeshComponent>(Components);
		for(UStaticMeshComponent* Mesh : Components) Mesh->SetRenderCustomDepth(true);
	}
}

void AMasterStructureAsset::EndCursorOver() const
{
	if(!GetBuildingMode())
	{
		TArray<UStaticMeshComponent*> Components;
		GetComponents<UStaticMeshComponent>(Components);
		for(UStaticMeshComponent* Mesh : Components) Mesh->SetRenderCustomDepth(false);
	}
}


//Normal Mode 
bool AMasterStructureAsset::IsClicked() const
{
	return BIsClicked;
}


//Building Mode
bool AMasterStructureAsset::GetBuildingMode() const
{
	return BBuildingMode;
}

void AMasterStructureAsset::SetBuildingMode(const bool BuildingModeActive)
{
	BBuildingMode = BuildingModeActive;
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if(BuildingModeActive)
	{
		for(const UStaticMeshComponent* Mesh : Components)
		{
			FStaticMeshMaterials StaticMeshMaterials;
			StaticMeshMaterials.MaterialInterfaces = Mesh->GetMaterials();
			TempOriginalMaterials.Add(StaticMeshMaterials);
		}
		UpdateState();
	}else
	{
		for(int32 i = 0; i < TempOriginalMaterials.Num(); i++)
		{
			UStaticMeshComponent* Mesh = Components[i];
			for(int32 d = 0; d < Mesh->GetNumMaterials(); d++)
			{
				Mesh->SetMaterial(d, TempOriginalMaterials[i].MaterialInterfaces[d]);
			}
		}
	}
}

void AMasterStructureAsset::UpdateState()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	if (OverlappingActors.Num() == 0)
	{
		bIsPlacementValid = true;
		TArray<UStaticMeshComponent*> Components;
		GetComponents<UStaticMeshComponent>(Components);
		ChangeMaterialToValidOrInvalid(true);
	}else
	{
		bIsPlacementValid = false;
		TArray<UStaticMeshComponent*> Components;
		GetComponents<UStaticMeshComponent>(Components);
		ChangeMaterialToValidOrInvalid(false);
	}
}

bool AMasterStructureAsset::GetIsPlacementValid() const
{
	return bIsPlacementValid;
}

void AMasterStructureAsset::OnOverlapStatusChanged()
{
	 if(GetBuildingMode()) UpdateState();
}

void AMasterStructureAsset::ChangeMaterialToValidOrInvalid(const bool bValid) const
{
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);

	const ACityBuildPlayerController* PlayerController = Cast<ACityBuildPlayerController>(GetWorld()->GetFirstPlayerController());
	const AGridManager* GridManager = PlayerController->GetGridManager();
	if(bValid)
	{
		for(UStaticMeshComponent* Mesh : Components)
		{
			for(int32 d = 0; d < Mesh->GetNumMaterials(); d++)
			{
				Mesh->SetMaterial(d, GridManager->GetValidMaterial_Dynamic());
			}
		}
	}else
	{
		for(UStaticMeshComponent* Mesh : Components)
		{
			for(int32 d = 0; d < Mesh->GetNumMaterials(); d++)
			{
				Mesh->SetMaterial(d, GridManager->GetInvalidMaterial_Dynamic());
			}
		}
	}
}


