// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"

#include "World/Structs/FStaticMeshMaterials.h"
#include "GameFramework/Actor.h"
#include "MasterStructureAsset.generated.h"

UCLASS()
class CITYBUILD_API AMasterStructureAsset : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterStructureAsset();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup")
		UTexture2D* ThumbnailImage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
		UTexture2D* ThumbnailImageClicked = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
		FName InImageName = FName("");

	// Building Data
	UPROPERTY(EditAnywhere, Category="Building Data")	// Name of the Building
		FString BuildingName;
	
	UPROPERTY(EditAnywhere, Category="Building Data")	// Base Cost of the Building
		int32 BuildingCost;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Cost to keep the Building Running
		int32 BuildingUpkeepCost;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Attractiveness of the Building | Higher Attractiveness can Raise the Price an will be sold faster
		int32 Attractiveness;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Presence of the Surrounding | Will effect the Attractiveness both Positive and Negative
		int32 Presence;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Level of the Building
		int32 BuildingLevel;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Type of the Building
		FString BuildingType;
	

protected:
	
	UFUNCTION()
		virtual void MouseClicked();
	UFUNCTION()
		virtual void BeginCursorOver() const;
	UFUNCTION()
		virtual void EndCursorOver() const;

public:
	//Normal Mode
	UFUNCTION()
		bool IsClicked() const;

protected:
	//Normal Mode
	UPROPERTY(EditAnywhere, Category="Clicked")
		bool BIsClicked;

public:
	//Building Mode
	UFUNCTION()
		bool GetBuildingMode() const;

	UFUNCTION()
		void SetBuildingMode(const bool BuildingModeActive);

	UFUNCTION()
		void UpdateState();

	UFUNCTION()
		bool GetIsPlacementValid() const;
	
protected:
	//Building Mode
	UFUNCTION()
		virtual void OnOverlapStatusChanged();
	
	UPROPERTY(EditAnywhere, Category="BuildingMode")
		bool BBuildingMode;
	
	UPROPERTY(EditAnywhere, Category = "BuildingMode")
		bool bIsPlacementValid;

	UPROPERTY(EditAnywhere, Category = "BuildingMode")
		TArray<FStaticMeshMaterials> TempOriginalMaterials;

private:
	UFUNCTION()
		void ChangeMaterialToValidOrInvalid(const bool bValid) const;
};
