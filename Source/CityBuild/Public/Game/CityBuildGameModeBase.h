// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CityBuildGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API ACityBuildGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACityBuildGameModeBase();

	virtual void BeginPlay() override;
};
