// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "World/Structures/MasterBuildingAsset.h"
#include "MasterStreetAsset.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API AMasterStreetAsset : public AMasterStructureAsset
{
	GENERATED_BODY()

	// Street Data
	UPROPERTY(EditAnywhere, Category="Street Data")	// Lanes of the Street
		int32 Lanes;

	UPROPERTY(EditAnywhere, Category="Street Data")	// Is One Way Street
		bool IsOneWay;

	//@todo: Access: Residents, Police , Trucks...
	
public:	
	// Sets default values for this actor's properties
	AMasterStreetAsset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
