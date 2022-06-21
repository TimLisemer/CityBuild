// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "World/Structures/MasterBuildingAsset.h"
#include "TestBuilding.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API ATestBuilding final: public AMasterBuildingAsset
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
