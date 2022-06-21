// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "World/Structs/FGridArray.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

class ACityBuildPlayerController;
UCLASS()
class CITYBUILD_API AGridManager final: public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();
	UFUNCTION()
		void SetPlayerController(ACityBuildPlayerController* Pc);

	UFUNCTION()
		void ActivateGrid(const bool BuildModeActive);

	UFUNCTION()
		virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void PopulateGrid();

	//10 = 10*10 Size Grid
	UPROPERTY(EditAnywhere, Category="Grid")
		int32 GridSize = 56;

	//Units Between Each Grid Square
	UPROPERTY(EditAnywhere, Category="Grid")
		float WorldGridSize = 100.001f;

	UPROPERTY(EditAnywhere, Category="Grid")
		TArray<FGridArray> GridArray;

	//Material
	UPROPERTY(EditAnywhere, Category = "Material")
		UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
		UMaterialInterface* ValidMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
		UMaterialInterface* InvalidMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* DefaultMaterial_Dynamic;

	UPROPERTY()
		UMaterialInstanceDynamic* ValidMaterial_Dynamic;

	UPROPERTY()
		UMaterialInstanceDynamic* InvalidMaterial_Dynamic;

	UPROPERTY()
		UMaterialInstanceDynamic* InvisibleMaterial_Dynamic;

public:
	UFUNCTION()
		UMaterialInstanceDynamic* GetDefaultMaterial_Dynamic() const;

	UFUNCTION()
		UMaterialInstanceDynamic* GetValidMaterial_Dynamic() const;

	UFUNCTION()
		UMaterialInstanceDynamic* GetInvalidMaterial_Dynamic() const;

	UFUNCTION()
		UMaterialInstanceDynamic* GetInvisibleMaterial_Dynamic() const;

	UFUNCTION()
		float GetWorldGridSize() const;

private:
	UPROPERTY()
	ACityBuildPlayerController* PlayerController;

	//Neighbours
public:

	UFUNCTION()
		void ClearCells();

	UFUNCTION()
		void SetupMaterial();
	
	UFUNCTION()
		AGridCell* GetNorthernNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetSouthernNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetEasternNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetWesternNeighbour(const AGridCell* StartCell);

	UFUNCTION()
		AGridCell* GetNorthEastNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetNorthWestNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetSouthEastNeighbour(const AGridCell* StartCell);
	UFUNCTION()
		AGridCell* GetSouthWestNeighbour(const AGridCell* StartCell);


	//Building Placement
public:
	UFUNCTION()
		static void MakeCellsInvisible(TArray<AGridCell*> Cells);
	
};
