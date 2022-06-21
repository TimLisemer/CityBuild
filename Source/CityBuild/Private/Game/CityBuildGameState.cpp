// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "Game/CityBuildGameState.h"

FDateTime ACityBuildGameState::GetDateTime() const
{
	return DateTime;
}

FString ACityBuildGameState::GetTimeString() const
{
	return FText::AsDateTime(DateTime).ToString();
}

void ACityBuildGameState::SetCurrentSpeedSetting(const int32 Speed)
{
	if(Speed >= 0 && Speed <= 3) CurrentSpeedSetting = Speed;
}

int32 ACityBuildGameState::GetCurrentSpeedSetting() const
{
	return CurrentSpeedSetting;
}

void ACityBuildGameState::SetDayNightCycle(ADayNightCycle* Cycle)
{
	DayNightCycle = Cycle;
}

bool ACityBuildGameState::IsPauseMenuOpen() const
{
	return BOpenedPauseMenu;
}

void ACityBuildGameState::SetOpenedPauseMenu(const bool Pause)
{
	BOpenedPauseMenu = Pause;
}

TArray<AMasterStructureAsset*> ACityBuildGameState::GetAvailableBuildings()
{
	return AvailableBuildings;
}

void ACityBuildGameState::AddBuilding(AMasterStructureAsset* Building)
{
	AvailableBuildings.Add(Building);
}

void ACityBuildGameState::CalculateTime(float AddSeconds)
{
	AddSeconds = AddSeconds + TempSeconds;
	if (DayNightCycle) DayNightCycle->SetLight(DateTime.GetHour()*60*60 + DateTime.GetMinute()*60 + DateTime.GetSecond() + AddSeconds);
	if(AddSeconds < 1)
	{
		TempSeconds = AddSeconds;
	}else
	{
		TempSeconds = 0.0f;
		int32 Second = DateTime.GetSecond() + AddSeconds;
		int32 Minute = DateTime.GetMinute();
		int32 Hour = DateTime.GetHour();
		int32 Day = DateTime.GetDay();
		int32 Month = DateTime.GetMonth();
		int32 Year = DateTime.GetYear();
		bool Finished = false;
		while(!Finished)
		{
			Finished = true;
			if(Second >= 60)
			{
				Second = Second - 60;
				Minute ++;
				if(Second >= 60) Finished = false;
			}
			if(Minute >= 60)
			{
				Minute = Minute - 60;
				Hour ++;
				if(Minute >= 60) Finished = false;
			}
			if(Hour >= 24)
			{
				Hour = Hour - 24;
				Day ++;
				if(Hour >= 24) if(Minute >= 60) Finished = false;
			}

			if(Month == 2)
			{
				if(Year % 4 == 0)
				{
					if(Year % 100 == 0)
					{
						if(Year % 400 != 0)
						{
							if(Day > 29)
							{
								Day = Day - 29;
								Month ++;
								if(Day > 29) Finished = false;
							}
						}else if(Day >= 29)
						{
							Day = Day - 28;
							Month ++;
							if(Day >= 29) Finished = false;
						}
					}else
					{
						if(Day > 29)
						{
							Day = Day - 29;
							Month ++;
							if(Day > 29) Finished = false;
						}
					}
				}else if(Day >= 29)
				{
					Day = Day - 28;
					Month ++;
					if(Day >= 29) Finished = false;
				}

		
			}else if(Month == 4 || Month == 6 || Month == 9 || Month == 11)
			{
				if(Day > 30)
				{
					Day = Day = Day - 30;
					Month++;
					if(Day > 30) Finished = false;
				}
			}else if(Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10  || Month == 12)
			{
				if(Day > 31)
				{
					Day = Day = Day - 31;
					Month++;
					if(Day > 31) Finished = false;
				}
			}

			if(Month >= 13)
			{
				Month = Month - 12;
				Year++;
				if(Month >= 13) Finished = false;
			}
		}
		if(Year >= 9999) Year = 0001;
	
		DateTime = FDateTime(Year, Month, Day, Hour, Minute, Second);
	}
}

void ACityBuildGameState::UpdateTime()
{
	if(!IsPauseMenuOpen())
	{
		const float ServerTime = GetServerWorldTimeSeconds();
		if(TempServerTimeSeconds == 0) TempServerTimeSeconds = ServerTime;
		if(ServerTime - TempServerTimeSeconds >= 0.01f)
		{
			TempServerTimeSeconds = ServerTime;
			switch (CurrentSpeedSetting)
			{
			case 3:
				CurrentSpeeds = Speed0 * Speed1 * Speed2 * Speed3;
				break;
			case 2:
				CurrentSpeeds = Speed0 * Speed1 * Speed2;
				break;
			case 1:
				CurrentSpeeds = Speed0 * Speed1;
				break;
			case 0:
				CurrentSpeeds = Speed0;
				break;
			default:
				CurrentSpeeds = Speed0;
				break;
			}
			if(CurrentSpeeds >= 0) CalculateTime(CurrentSpeeds / 100.0f);
		}
	}
}
