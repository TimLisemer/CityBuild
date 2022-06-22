// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "World/Structures/MasterStructureAsset.h"
#include "MasterBuildingAsset.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API AMasterBuildingAsset : public AMasterStructureAsset
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterBuildingAsset();

	// Building Data
	UPROPERTY(EditAnywhere, Category="Building Data")	// Amount of Residents living inside the Building
		int32 CurrentResidents;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Maximum Amount of Citizens living in the Building
		int32 MaxResidents;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Amount of Children living in the Building
		int32 Kids;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Amount of Adults living in the Building
		int32 Adults;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Amount of Retired living in the Building
		int32 Retired;

	UPROPERTY(EditAnywhere, Category="Building Data")	// Name of the Street
		FString StreetName;

	UPROPERTY(EditAnywhere, Category="Building Data")	// HouseNumber of the Building
		int32 HouseNumber;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
