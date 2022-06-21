// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "UI/Elements/BuildingButton.h"

#include "UI/Elements/FBuildingButtonStyle.h"
//#include "SlatePublic/Brushes/SlateImageBrush.h"

UBuildingButton::UBuildingButton()
{
}

void UBuildingButton::PostLoad()
{
	Super::PostLoad();
	/*
	const FString PathToLoad = "/Game/Design/UI/GameMainHud/BuildingButton";
	SetStyle(FBuildingButtonStyle("BuildingButton", FVector2D(75.0f, 95.0f), PathToLoad));
	*/
}

void UBuildingButton::LoadStyle()
{
	if(!BuildingClass)
	{
		BuildingClass = BpPath.TryLoadClass<AMasterStructureAsset>();
		LoadStyle();
	}else
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AMasterStructureAsset* Asset = GetWorld()->SpawnActor<AMasterStructureAsset>(BuildingClass, FVector(0.0f, 0.0f, -1000000.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
		
		SetStyle(FBuildingButtonStyle("null", FVector2D(100.0f, 86.0f), Asset->ThumbnailImage, Asset->ThumbnailImageClicked));
		GetWorld()->DestroyActor(Asset);
	}
}

void UBuildingButton::SetBpPath(const FSoftClassPath Path)
{
	BpPath = Path;
	LoadStyle();
}

TSubclassOf<class AMasterStructureAsset> UBuildingButton::GetBuildingClass()
{
	if(!BuildingClass) BuildingClass = BpPath.TryLoadClass<AMasterStructureAsset>();
	return BuildingClass;
}

void UBuildingButton::SetActive(const bool Active)
{
	bActive = Active;

	if(!BuildingClass)
	{
		BuildingClass = BpPath.TryLoadClass<AMasterStructureAsset>();
		SetActive(Active);
	}else
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AMasterStructureAsset* Asset = GetWorld()->SpawnActor<AMasterStructureAsset>(BuildingClass, FVector(0.0f, 0.0f, -1000000.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);

		if(Active)
		{
			SetStyle(FBuildingButtonStyle("null", FVector2D(100.0f, 86.0f), Asset->ThumbnailImageClicked, Asset->ThumbnailImageClicked));
		}else
		{
			SetStyle(FBuildingButtonStyle("null", FVector2D(100.0f, 86.0f), Asset->ThumbnailImage, Asset->ThumbnailImageClicked));
		}
		GetWorld()->DestroyActor(Asset);
	}
}

bool UBuildingButton::GetActive() const
{
	return bActive;
}

/*
void UBuildingButton::SetBuildingAsset(ABuildingAsset* Asset)
{
	BuildingAsset = Asset;
	if(BuildingAsset)
		SetStyle(FBuildingButtonStyle("BuildingButton", FVector2D(75.0f, 95.0f), BuildingAsset->ThumbnailImage, BuildingAsset->ThumbnailImageClicked));
}
*/
