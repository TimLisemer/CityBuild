// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

class ACityBuildPlayerController;
UCLASS()
class CITYBUILD_API AGridCell final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridCell();
	UFUNCTION()
		void SetPlayerController(ACityBuildPlayerController* Pc);

	UFUNCTION()
		void SetCellActive(const bool Active);

	UFUNCTION()
		void ChangeMaterial(UMaterialInterface* Material) const;

	UFUNCTION()
		void SetCellSelected(const bool Selected);

	UFUNCTION()
		bool IsCellSelected() const;

	UFUNCTION()
		int32 GetPosI() const;

	UFUNCTION()
		int32 GetPosD() const;

	UFUNCTION()
		void SetPosition(const int32 I, const int32 D);

	UFUNCTION()
		FVector2D GetLocation() const;

	UFUNCTION()
		void SetLocation(const FVector2D Loc);

	UFUNCTION()
		void SetVisibility(const bool bVisibility) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Todo: Delete
	UFUNCTION()
		virtual void BeginCursorOver() const;
	UFUNCTION()
		virtual void EndCursorOver() const;
		*/

private:

	UPROPERTY()
	ACityBuildPlayerController* PlayerController;

	UPROPERTY()
	bool bActive;

	UPROPERTY()
	bool bSelected;

	UPROPERTY()
	int32 PosI;

	UPROPERTY()
	int32 PosD;

	UPROPERTY()
	FVector2D Location;

};
