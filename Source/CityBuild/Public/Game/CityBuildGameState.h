// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "World/DayNightCycle.h"
#include "World/Structures/MasterStructureAsset.h"

#include "CityBuildGameState.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API ACityBuildGameState final: public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
		FDateTime GetDateTime() const;

	UFUNCTION()
		FString GetTimeString() const;

	UFUNCTION()
		void CalculateTime(float AddSeconds);

	UFUNCTION()
		void UpdateTime();

	UFUNCTION()
		void SetCurrentSpeedSetting(const int32 Speed);

	UFUNCTION()
		int32 GetCurrentSpeedSetting() const;

	UFUNCTION()
		void SetDayNightCycle(ADayNightCycle* Cycle);

	UFUNCTION()
		bool IsPauseMenuOpen() const;

	UFUNCTION()
		void SetOpenedPauseMenu(const bool Pause);

	UFUNCTION()
		TArray<AMasterStructureAsset*> GetAvailableBuildings();

	UFUNCTION()
		void AddBuilding(AMasterStructureAsset* Building);

protected:

	UPROPERTY()
	TArray<AMasterStructureAsset*> AvailableBuildings;

	UPROPERTY(BlueprintReadWrite, Category="PauseMenu")
	bool BOpenedPauseMenu;
	
	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 CurrentSpeeds;
	
	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 CurrentSpeedSetting = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Time")
	FDateTime DateTime = FDateTime::Now();

	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 Speed0 = 1;
	
	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 Speed1 = 60;

	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 Speed2 = 60;

	UPROPERTY(BlueprintReadWrite, Category="Time")
	int32 Speed3 = 24;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	class ADayNightCycle* DayNightCycle;

private:
	int32 TempServerTimeSeconds = 0;
	float TempSeconds = 0;
};
