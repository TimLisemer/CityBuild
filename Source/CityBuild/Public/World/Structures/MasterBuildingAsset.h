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

	// Residents
	UPROPERTY(EditAnywhere, Category="Residents")	// Building will be abandoned if there are < MinResidents living there
	int32 MinResidents;

	UPROPERTY(EditAnywhere, Category="Residents")	// Maximum Amount of Citizens living in the Building
	int32 MaxResidents;

	UPROPERTY(EditAnywhere, Category="Residents")	// Amount of Children living in the Building
	int32 Kids;

	UPROPERTY(EditAnywhere, Category="Residents")	// Amount of Adults living in the Building
	int32 Adults;

	UPROPERTY(EditAnywhere, Category="Residents")	// Amount of Retired living in the Building
	int32 Retired;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
