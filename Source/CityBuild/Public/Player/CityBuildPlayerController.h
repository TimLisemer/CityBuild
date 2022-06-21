// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "UI/CityBuildHud.h"
#include "Player/CameraPawnCityBuild.h"
#include "Game/CityBuildGameState.h"
#include "World/Structures/MasterStructureAsset.h"
#include "World/Grid/GridManager.h"
#include "CityBuildPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API ACityBuildPlayerController final: public APlayerController
{
	GENERATED_BODY()

public:

	ACityBuildPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	// Variables for Margin
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float OuterMarginInPercent = 5.0f;
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float InnerMarginInPercent = 1.25f;

private:
	void MoveForward(const float AxisValueX);
	void MoveRight(const float AxisValueY);
	void IncreaseSpeedModifier();
	void DecreaseSpeedModifier();
	void ZoomIn();
	void ZoomOut();
	void ResetZoom();
	void PanCameraLeft();
	void PanCameraRight();
	void PanReset();
	void ShowDeveloperInfo();
	void OpenPauseMenu();
	void HandleLeftClick();
	void HandleRightClick();
	//Build
protected:
	UPROPERTY(Category = "Pause Menu", BlueprintReadOnly)
		bool bIsInPauseMenu;

	UPROPERTY(EditAnywhere, Category = "Build")
		bool bPlacementModeEnabled = false;

	UPROPERTY(EditAnywhere, Category = "Build")
		AMasterStructureAsset* PlaceableActor;

	UPROPERTY(EditAnywhere, Category = "Grid")
		AGridManager* GridManager;
	
	UPROPERTY(EditAnywhere, Category = "Build")
		TSubclassOf<class AMasterStructureAsset> TempBuildingClass;
public:
	UFUNCTION()
		void SetPlacementModeEnabled(const bool IsEnabled, const TSubclassOf<class AMasterStructureAsset> BuildingClass);

	UFUNCTION()
		void UpdatePlacement(const AGridCell* Cell) const;

	UFUNCTION()
		void SpawnBuilding();

	UFUNCTION()
		AGridManager* GetGridManager() const;

	UFUNCTION()
		bool GetPlacementModeEnabled() const;
	//End Build

	
	//Class Declarations
protected:
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		class ACityBuildHud* CityBuildHud;
	
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		class ACameraPawnCityBuild* CityBuildPawn;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		class UCameraMovementComponent* CameraMovementComponent;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		class ACityBuildGameState* CityBuildGameState;

public:
	ACityBuildHud* GetCityBuildHud() const;
	ACameraPawnCityBuild* GetCityBuildPawn() const;
	UCameraMovementComponent* GetCameraMovementComponent() const;
	ACityBuildGameState* GetCityBuildGameState() const;
	//End Class Declarations
};
