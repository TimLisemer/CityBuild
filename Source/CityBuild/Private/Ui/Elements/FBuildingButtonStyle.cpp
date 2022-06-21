// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "UI/Elements/FBuildingButtonStyle.h"

#include "Brushes/SlateImageBrush.h"
#include "Engine/Texture2D.h"
//#include "SlatePublic/Brushes/SlateImageBrush.h"

FBuildingButtonStyle::FBuildingButtonStyle() : ImageNormal(nullptr), ImageClicked(nullptr)
{
}

/*
FBuildingButtonStyle::FBuildingButtonStyle(const FName& InImageName, const FVector2D ImageSize, const FString PathToLoad)
{
	ImageNormal = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(PathToLoad)));
	FSlateImageBrush Brush = FSlateImageBrush(InImageName, ImageSize);
	Brush.SetResourceObject(ImageNormal);
	ImageClicked = ImageNormal;
	SetNormal(Brush);
	SetHovered(Brush);
	SetPressed(Brush);
}
*/

FBuildingButtonStyle::FBuildingButtonStyle(const FName& InImageName, const FVector2D ImageSize,
	UTexture2D* ThumbnailImageNormal, UTexture2D* ThumbnailImageClicked)
{
	ImageNormal = ThumbnailImageNormal;
	ImageClicked = ThumbnailImageClicked;

	FSlateImageBrush BrushNormal = FSlateImageBrush(InImageName, ImageSize);
	BrushNormal.SetResourceObject(ImageNormal);

	FSlateImageBrush BrushClicked = FSlateImageBrush(InImageName, ImageSize);
	BrushClicked.SetResourceObject(ThumbnailImageClicked);

	SetNormal(BrushNormal);
	SetHovered(BrushClicked);
	SetPressed(BrushClicked);
}
