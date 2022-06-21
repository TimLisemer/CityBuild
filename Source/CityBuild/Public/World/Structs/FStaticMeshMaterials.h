#pragma once

#include "CoreMinimal.h"
#include "FStaticMeshMaterials.generated.h"

USTRUCT(BlueprintType)
struct FStaticMeshMaterials
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<UMaterialInterface*> MaterialInterfaces;
};