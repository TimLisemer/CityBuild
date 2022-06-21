// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "World/DayNightCycle.h"

#include "Game/CityBuildGameState.h"
#include "Misc/OutputDeviceNull.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();
	Cast<ACityBuildGameState>(GetWorld()->GetGameState())->SetDayNightCycle(this);
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADayNightCycle::SetLight(const float Time) const
{
	if(LightSource)
	{
		float TurnRate = Time / 86400 * 360;
		if(TurnRate + 90 > 360)
		{
			TurnRate = (TurnRate + 90) - 360;
		}else TurnRate = TurnRate + 90;
		LightSource->SetActorRotation(FRotator(TurnRate, 0, 0));
	}

	if(Sun)
	{
		FOutputDeviceNull FOutputDeviceNull;
		Sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), FOutputDeviceNull, nullptr, true);
	}
}

