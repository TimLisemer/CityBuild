// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "UI/CityBuildHud.h"

#include "Ui/SActorWidgetComponent.h"

// Default Functions
ACityBuildHud::ACityBuildHud(){}
void ACityBuildHud::BeginPlay()
{
	Super::BeginPlay();
}
void ACityBuildHud::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void ACityBuildHud::DrawHUD()
{
	Super::DrawHUD();
}

// Load Widget Function
UUserWidget* ACityBuildHud::LoadWidget(TSubclassOf<UUserWidget> WidgetClass, UUserWidget* Widget, const FSoftClassPath BpPath) const
{
	if(!WidgetClass)
	{
		WidgetClass = BpPath.TryLoadClass<UUserWidget>();
	}
	if(WidgetClass)
	{
		if(!Widget) Widget = CreateWidget<>(GetWorld(), WidgetClass);
		if(Widget)
		{
			Widget->AddToViewport();
			return Widget;
		}
		UE_LOG(LogTemp, Error, TEXT("Error while loading Widget information"));
	}else UE_LOG(LogTemp, Error, TEXT("Error while loading Widget Blueprint"));
	UE_LOG(LogTemp, Error, TEXT("Error while loading Widget"));
	return nullptr;
}

//Load Widget Redirect Functions
bool ACityBuildHud::LoadDeveloperInfo()
{
	if(!F3Info || !F3Info->IsInViewport())
	{
		F3Info = Cast<UF3_Information>(LoadWidget(F3InfoClass, F3Info, BP_F3InfoRef));
		MouseMovement->SetBorderVisibility(true);
		if(F3Info != nullptr) return true;
		return false;
	}
	F3Info->RemoveFromViewport();
	MouseMovement->SetBorderVisibility(false);
	return !F3Info->IsInViewport();
}

bool ACityBuildHud::LoadMainGameMenu()
{
	const bool Mouse = LoadMouseMovementArea();
	MainGameHud = Cast<UMainGameHud>(LoadWidget(MainGameHudClass, MainGameHud, BP_MainGameHUD));
	if(MainGameHud != nullptr && Mouse) return true;
	return false;
}

bool ACityBuildHud::LoadPauseMenu()
{
	Pause = Cast<UPauseMenu>(LoadWidget(PauseClass, Pause, BP_PauseMenu));
	if(Pause != nullptr) return true;
	return false;
}

bool ACityBuildHud::LoadMouseMovementArea()
{
	if(!MouseMovement || !MouseMovement->IsInViewport())
	{
		MouseMovement = Cast<UMouseMovementArea>(LoadWidget(MouseMovementClass, MouseMovement, BP_MouseMovement));
		if(MouseMovement) MouseMovement->SetBorderVisibility(false);
		if(MouseMovement != nullptr) return true;
		return false;
	}
	MouseMovement->RemoveFromViewport();
	if(MouseMovement) MouseMovement->SetBorderVisibility(false);
	return !MouseMovement->IsInViewport();
}

bool ACityBuildHud::LoadBuildingWidget(AMasterStructureAsset* Building)
{
	/*
	BuildingWidget = Cast<UBuildingWidget>(LoadWidget(BuildingWidgetClass, BuildingWidget, BP_BuildingWidget));
	if(BuildingWidget)
	{
		BuildingWidget->SetOwningActor(Building);
		return true;
	}
	*/
	
	//Methode 1
	//USActorWidgetComponent* WidgetComponent = Building->CreateDefaultSubobject<USActorWidgetComponent>("WidgetComponent");
	//if(BuildingWidget) WidgetComponent->SetWidgetClass(BuildingWidget->GetClass());

	//Methode 2
    //BuildingWidget = Cast<UBuildingWidget>(BP_BuildingWidget.TryLoadClass<UBuildingWidget>());
	//if(BuildingWidget) BuildingWidget->SetOwningActor(Building);
	
	return true;
}

//Spare Variables
void ACityBuildHud::SetSpareVariable(const int32 Slot, const FString Description, const FString Variable) const
{
	if(F3Info) F3Info->SetSpareVariables(Slot, Description, Variable);
}

void ACityBuildHud::SetSpareVariableFloat(const int32 Slot, const FString Description, const float Variable) const
{
	if(F3Info) F3Info->SetSpareVariables(Slot, Description, FString::SanitizeFloat(Variable));
}


//F3 Information Widget Functions:
void ACityBuildHud::SetCameraSpeed(float &CameraSpeedX, float &CameraSpeedY, const FLinearColor Color) const
{
	if(F3Info)
	{
		if(CameraSpeedX == NULL && CameraSpeedY != NULL)
		{
			F3Info->UpdateCameraSpeed(FCString::Atof(*F3Info->CameraSpeedX->GetText().ToString()), CameraSpeedY, Color);
		}else if(CameraSpeedX != NULL && CameraSpeedY == NULL)
		{
			F3Info->UpdateCameraSpeed(CameraSpeedX, FCString::Atof(*F3Info->CameraSpeedY->GetText().ToString()), Color);
		}else if(CameraSpeedX == NULL && CameraSpeedY == NULL)
		{
			F3Info->UpdateCameraSpeed(FCString::Atof(*F3Info->CameraSpeedX->GetText().ToString()), FCString::Atof(*F3Info->CameraSpeedY->GetText().ToString()), Color);
		}else if(CameraSpeedX != NULL && CameraSpeedY != NULL)
		{
			F3Info->UpdateCameraSpeed(CameraSpeedX, CameraSpeedY, Color);
		}
		CameraSpeedX = 0;
		CameraSpeedY = 0;
	}
}

void ACityBuildHud::SetMouseMovementAreas(const float InnerArea, const float OuterArea, const float XOffset, const float YOffset) const
{
	if(MouseMovement && MouseMovement->IsInViewport()) MouseMovement->SetMouseMovementAreas(InnerArea, OuterArea, XOffset, YOffset);
}







