#pragma once

#include "CoreMinimal.h"
#include "World/Grid/GridCell.h"
#include "FGridArray.generated.h"

USTRUCT(BlueprintType)
struct FGridArray
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<AGridCell*> XGridArray;
};