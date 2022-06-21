// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"

#include "MainGameHud.h"
#include "MouseMovementArea.h"
#include "PauseMenu.h"
#include "GameFramework/HUD.h"
#include "UI/F3_Information.h"
#include "CityBuildHud.generated.h"


UCLASS()
class CITYBUILD_API ACityBuildHud final: public AHUD
{
	GENERATED_BODY()

public:
	ACityBuildHud();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	
	//Function to Load all Widget Classes
	UFUNCTION()
		bool LoadDeveloperInfo();
	
	UFUNCTION()
		bool LoadMainGameMenu();

	UFUNCTION()
		bool LoadPauseMenu();

	UFUNCTION()
		bool LoadMouseMovementArea();

	UFUNCTION()
		UUserWidget* LoadWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, const FSoftClassPath BpPath) const;

	//Declaration of Widget Classes
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> F3InfoClass;
	UPROPERTY(Category = "Widgets", BlueprintReadWrite)
		UF3_Information* F3Info;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MainGameHudClass;
	UPROPERTY(Category = "Widgets", BlueprintReadWrite)
		UMainGameHud* MainGameHud;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseClass;
	UPROPERTY(Category = "Widgets", BlueprintReadWrite)
		UPauseMenu* Pause;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MouseMovementClass;
	UPROPERTY(Category = "Widgets", BlueprintReadWrite)
		UMouseMovementArea* MouseMovement;

	//Path to Widget Blueprints
	const FSoftClassPath BP_MainGameHUD = FSoftClassPath(TEXT("/Game/UI/BP_MainGameHUD.BP_MainGameHUD_C"));
	const FSoftClassPath BP_F3InfoRef = FSoftClassPath(TEXT("/Game/UI/BP_F3Info.BP_F3Info_C"));
	const FSoftClassPath BP_PauseMenu = FSoftClassPath(TEXT("/Game/UI/BP_PauseMenu.BP_PauseMenu_C"));
	const FSoftClassPath BP_MouseMovement = FSoftClassPath(TEXT("/Game/UI/BP_MouseMovementArea.BP_MouseMovementArea_C"));

	
	// Functions of Widget Classes

	// Developer Info Widget
	UFUNCTION()
		void SetSpareVariable(const int32 Slot, const FString Description, const FString Variable) const;

	UFUNCTION()
		void SetSpareVariableFloat(const int32 Slot, const FString Description, const float Variable) const;

	UFUNCTION()
		void SetCameraSpeed(float &CameraSpeedX, float &CameraSpeedY, const FLinearColor Color) const;

	UFUNCTION()
		void SetMouseMovementAreas(const float InnerArea, const float OuterArea, const float XOffset, const float YOffset) const;

	
	
};
