// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "UI/MainGameHud.h"
// ReSharper disable once CppUnusedIncludeDirective --- https://forums.unrealengine.com/t/unresolved-external-symbol-fslatecolor-including-fix/141172
#include "Styling/SlateColor.h"
#include "Components/Button.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Components/TextBlock.h"
#include "Game/CityBuildGameState.h"
#include "UI/CityBuildHud.h"
#include "Player/CityBuildPlayerController.h"
#include "UI/Elements/BuildingButton.h"

UMainGameHud::UMainGameHud(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}

void UMainGameHud::NativeConstruct()
{
	Super::NativeConstruct();
	if(BOpenPauseMenu && BSpeed1 && BSpeed2 && BSpeed3 && BSpeed4)
	{
		BOpenPauseMenu->OnClicked.AddDynamic(this, &UMainGameHud::OpenPauseMenu);
		BSpeed1->OnClicked.AddDynamic(this, &UMainGameHud::Speed1);
		BSpeed2->OnClicked.AddDynamic(this, &UMainGameHud::Speed2);
		BSpeed3->OnClicked.AddDynamic(this, &UMainGameHud::Speed3);
		BSpeed4->OnClicked.AddDynamic(this, &UMainGameHud::Speed4);
		
		BuildingButton1->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton1);
		BuildingButton2->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton2);
		BuildingButton3->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton3);
		BuildingButton4->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton4);
		BuildingButton5->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton5);
		BuildingButton6->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton6);
		BuildingButton7->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton7);
		BuildingButton8->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton8);
		BuildingButton9->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton9);
		BuildingButton10->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton10);
		BuildingButton11->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton11);
		BuildingButton12->OnClicked.AddDynamic(this, &UMainGameHud::BuildButton12);

		BuildingButton1->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover1);
		BuildingButton2->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover2);
		BuildingButton3->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover3);
		BuildingButton4->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover4);
		BuildingButton5->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover5);
		BuildingButton6->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover6);
		BuildingButton7->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover7);
		BuildingButton8->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover8);
		BuildingButton9->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover9);
		BuildingButton10->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover10);
		BuildingButton11->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover11);
		BuildingButton12->OnHovered.AddDynamic(this, &UMainGameHud::BuildButtonHover12);

		BuildingButton1->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover1);
		BuildingButton2->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover2);
		BuildingButton3->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover3);
		BuildingButton4->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover4);
		BuildingButton5->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover5);
		BuildingButton6->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover6);
		BuildingButton7->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover7);
		BuildingButton8->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover8);
		BuildingButton9->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover9);
		BuildingButton10->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover10);
		BuildingButton11->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover11);
		BuildingButton12->OnUnhovered.AddDynamic(this, &UMainGameHud::BuildButtonHover12);
		
	} else UE_LOG(LogTemp, Error, TEXT("Error while loading Top Right Main Menu Buttons"));
}

void UMainGameHud::SetTime(const FString Time) const
{
	TimeBlock->SetText(FText::FromString(Time));
}

void UMainGameHud::OpenPauseMenu()
{
	Cast<ACityBuildHud>(GetPlayerContext().GetHUD())->LoadPauseMenu();
}

void UMainGameHud::Speed1()
{
	Cast<ACityBuildGameState>(GetPlayerContext().GetGameState())->SetCurrentSpeedSetting(0);;
	//todo: HighlightSpeedButton(1);
}

void UMainGameHud::Speed2()
{
	Cast<ACityBuildGameState>(GetPlayerContext().GetGameState())->SetCurrentSpeedSetting(1);
	//todo: HighlightSpeedButton(2);
}

void UMainGameHud::Speed3()
{
	Cast<ACityBuildGameState>(GetPlayerContext().GetGameState())->SetCurrentSpeedSetting(2);
	//todo: HighlightSpeedButton(3);
}

void UMainGameHud::Speed4()
{
	Cast<ACityBuildGameState>(GetPlayerContext().GetGameState())->SetCurrentSpeedSetting(3);
	//todo: HighlightSpeedButton(4);
}

void UMainGameHud::ManageButtons()
{
	
}

void UMainGameHud::SetActiveBuildButton(UBuildingButton* Button, const bool NewActiveStatus)
{
	if(!Button) return;
	if(!PlayerController) PlayerController = Cast<ACityBuildPlayerController>(GetPlayerContext().GetPlayerController());
	if(!NewActiveStatus)
	{
		ActiveBuildButton = nullptr;
		Button->SetActive(false);
		if(Button->GetBuildingClass())
		{
			PlayerController->SetPlacementModeEnabled(false, Button->GetBuildingClass());
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Building Button has no Building Class"));
		}
	}else
	{
		if(ActiveBuildButton) ActiveBuildButton->SetActive(false);
		ActiveBuildButton = Button;
		Button->SetActive(true);
		if(Button->GetBuildingClass())
		{
			PlayerController->SetPlacementModeEnabled(true, Button->GetBuildingClass());
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("Building Button has no Building Class"));
		}
	}
}

void UMainGameHud::BuildButtonHover1()
{
	BuildButtonHover(BuildingButton1);
}

void UMainGameHud::BuildButtonHover2()
{
	BuildButtonHover(BuildingButton2);
}

void UMainGameHud::BuildButtonHover3()
{
	BuildButtonHover(BuildingButton3);
}

void UMainGameHud::BuildButtonHover4()
{
	BuildButtonHover(BuildingButton4);
}

void UMainGameHud::BuildButtonHover5()
{
	BuildButtonHover(BuildingButton5);
}

void UMainGameHud::BuildButtonHover6()
{
	BuildButtonHover(BuildingButton6);
}

void UMainGameHud::BuildButtonHover7()
{
	BuildButtonHover(BuildingButton7);
}

void UMainGameHud::BuildButtonHover8()
{
	BuildButtonHover(BuildingButton8);
}

void UMainGameHud::BuildButtonHover9()
{
	BuildButtonHover(BuildingButton9);
}

void UMainGameHud::BuildButtonHover10()
{
	BuildButtonHover(BuildingButton10);
}

void UMainGameHud::BuildButtonHover11()
{
	BuildButtonHover(BuildingButton11);
}

void UMainGameHud::BuildButtonHover12()
{
	BuildButtonHover(BuildingButton12);
}


void UMainGameHud::BuildButton1()
{
	BuildButtonOnClick(BuildingButton1);
}

void UMainGameHud::BuildButton2()
{
	BuildButtonOnClick(BuildingButton2);
}

void UMainGameHud::BuildButton3()
{
	BuildButtonOnClick(BuildingButton3);
}

void UMainGameHud::BuildButton4()
{
	BuildButtonOnClick(BuildingButton4);
}

void UMainGameHud::BuildButton5()
{
	BuildButtonOnClick(BuildingButton5);
}

void UMainGameHud::BuildButton6()
{
	BuildButtonOnClick(BuildingButton6);
}

void UMainGameHud::BuildButton7()
{
	BuildButtonOnClick(BuildingButton7);
}

void UMainGameHud::BuildButton8()
{
	BuildButtonOnClick(BuildingButton8);
}

void UMainGameHud::BuildButton9()
{
	BuildButtonOnClick(BuildingButton9);
}

void UMainGameHud::BuildButton10()
{
	BuildButtonOnClick(BuildingButton10);
}

void UMainGameHud::BuildButton11()
{
	BuildButtonOnClick(BuildingButton11);
}

void UMainGameHud::BuildButton12()
{
	BuildButtonOnClick(BuildingButton12);
}

void UMainGameHud::BuildButtonOnClick(UBuildingButton* Button)
{
	if(ActiveBuildButton == nullptr)
	{
		SetActiveBuildButton(Button, true);
	}else if(ActiveBuildButton == Button)
	{
		SetActiveBuildButton(Button, false);
	}else
	{
		SetActiveBuildButton(Button, true);
	}
}

void UMainGameHud::BuildButtonHover(const UBuildingButton* Button)
{
	if(Button->IsHovered())
	{
		//UE_LOG(LogTemp, Display, TEXT("BuildButton Hovered"));
	}else
	{
		//UE_LOG(LogTemp, Display, TEXT("BuildButton Un hovered"));
	}
}
