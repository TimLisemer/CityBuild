// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Engine//DirectionalLight.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

UCLASS()
class CITYBUILD_API ADayNightCycle final: public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLight(const float Time) const;

	UPROPERTY(EditAnywhere, Category = "Sky")
	AActor* Sun;	//Sky Sphere

	UPROPERTY(EditAnywhere, Category = "Sky")
	ADirectionalLight* LightSource;
};
