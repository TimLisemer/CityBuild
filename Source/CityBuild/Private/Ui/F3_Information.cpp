// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "UI/F3_Information.h"
// ReSharper disable once CppUnusedIncludeDirective --- https://forums.unrealengine.com/t/unresolved-external-symbol-fslatecolor-including-fix/141172
#include "Styling/SlateColor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

UF3_Information::UF3_Information(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UF3_Information::NativeConstruct()
{
	Super::NativeConstruct();
	if(SpareVariable0 && SpareVariable1 && SpareVariable2 && SpareVariable3 && SpareVariable4 && SpareVariable5 &&
		SpareVariable6 && SpareVariable7 && SpareVariable8 && SpareVariable9 && SpareVariable10  && SpareVariable11 &&
		SpareVariable12 && SpareVariable13 && SpareVariable14 && SpareVariable15)
	{
		TextBlocks.Add(SpareVariable0);
		TextBlocks.Add(SpareVariable1);
		TextBlocks.Add(SpareVariable2);
		TextBlocks.Add(SpareVariable3);
		TextBlocks.Add(SpareVariable4);
		TextBlocks.Add(SpareVariable5);
		TextBlocks.Add(SpareVariable6);
		TextBlocks.Add(SpareVariable7);
		TextBlocks.Add(SpareVariable8);
		TextBlocks.Add(SpareVariable9);
		TextBlocks.Add(SpareVariable10);
		TextBlocks.Add(SpareVariable11);
		TextBlocks.Add(SpareVariable12);
		TextBlocks.Add(SpareVariable13);
		TextBlocks.Add(SpareVariable14); 
		TextBlocks.Add(SpareVariable15);
	}
}


void UF3_Information::UpdateCameraSpeed(const float SpeedX, const float SpeedY, const FLinearColor Color) const
{
	if(CameraSpeedX && CameraSpeedY)
	{
		CameraSpeedX->SetText(FText::FromString("Camera Speed X: " + FString::SanitizeFloat(SpeedX)));
		CameraSpeedY->SetText(FText::FromString("Camera Speed Y: " + FString::SanitizeFloat(SpeedY)));
		CameraSpeedX->SetColorAndOpacity(Color);
		CameraSpeedY->SetColorAndOpacity(Color);
	}
}

void UF3_Information::SetSpareVariables(const int32 TextBlocksSlot, const FString Description, const FString Variable)
{
	if(TextBlocks[TextBlocksSlot]) TextBlocks[TextBlocksSlot]->SetText(FText::FromString(Description + ": " + Variable));
}





