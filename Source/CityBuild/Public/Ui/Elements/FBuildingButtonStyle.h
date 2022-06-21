#pragma once

#include "Styling/SlateTypes.h" 
#include "FBuildingButtonStyle.generated.h"

USTRUCT(BlueprintType)
struct FBuildingButtonStyle : public FButtonStyle
{
	GENERATED_USTRUCT_BODY()
public:
	FBuildingButtonStyle();

	FBuildingButtonStyle(const FName& InImageName, const FVector2D ImageSize, UTexture2D* ThumbnailImageNormal, UTexture2D* ThumbnailImageClicked);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* ImageNormal;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* ImageClicked;
};
