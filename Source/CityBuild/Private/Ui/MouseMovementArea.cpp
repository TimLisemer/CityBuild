// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "UI/MouseMovementArea.h"
#include "Components/CanvasPanelSlot.h"


UMouseMovementArea::UMouseMovementArea(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UMouseMovementArea::NativeConstruct()
{
	Super::NativeConstruct();
	if(BorderTop && BorderTop1 && BorderRight && BorderRight1 && BorderLeft && BorderLeft1 && BorderBottom && BorderBottom1)
	{
		Borders.Add(BorderTop);
		Borders.Add(BorderTop1);
		Borders.Add(BorderLeft);
		Borders.Add(BorderLeft1);
		Borders.Add(BorderRight);
		Borders.Add(BorderRight1);
		Borders.Add(BorderBottom);
		Borders.Add(BorderBottom1);
	}
	if(BorderTopLeftX && BorderTopLeftY && BorderTopRightX && BorderTopRightY && BorderBottomLeftX && BorderBottomLeftY && BorderBottomRightX && BorderBottomRightY)
	{
		Borders.Add(BorderTopLeftX);
		Borders.Add(BorderTopLeftY);
		Borders.Add(BorderTopRightX);
		Borders.Add(BorderTopRightY);
		Borders.Add(BorderBottomLeftX);
		Borders.Add(BorderBottomLeftY);
		Borders.Add(BorderBottomRightX);
		Borders.Add(BorderBottomRightY);
	}

	if(BorderTopLeftYOuter && BorderTopLeftXOuter && BorderTopRightYOuter && BorderTopRightXOuter && BorderBottomLeft && BorderBottomRight)
	{
		Borders.Add(BorderTopLeftYOuter);
		Borders.Add(BorderTopLeftXOuter);
		Borders.Add(BorderTopRightYOuter);
		Borders.Add(BorderTopRightXOuter);
		Borders.Add(BorderBottomLeft);
		Borders.Add(BorderBottomRight);
	}
	SetBorderVisibility(false);
}

bool UMouseMovementArea::SetBorderVisibility(const bool Visible)
{
	if(Visible)
	{
		for (UCustomBorder* Border : Borders) Border->SetRenderOpacity(0.3f);
	}else
	{
		for (UCustomBorder* Border : Borders) Border->SetRenderOpacity(0.0f);
	}
	return bVisibility = !Visible;
}

bool UMouseMovementArea::GetVisibility() const
{
	return bVisibility;
}

void UMouseMovementArea::SetMouseMovementAreas(const float InnerArea, const float OuterArea, const float XOffset, const float YOffset) const
{
	if(BorderTop && BorderTop1 && BorderRight && BorderRight1 && BorderLeft && BorderLeft1 && BorderBottom && BorderBottom1)
	{
		Cast<UCanvasPanelSlot>(BorderTop->Slot)->SetOffsets(FVector2D(XOffset,OuterArea));
		Cast<UCanvasPanelSlot>(BorderTop->Slot)->SetPosition(FVector2D(XOffset,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTop1->Slot)->SetOffsets(FVector2D(XOffset,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTop1->Slot)->SetPosition(FVector2D(XOffset,0));

		Cast<UCanvasPanelSlot>(BorderLeft->Slot)->SetOffsets(FVector2D(InnerArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderLeft->Slot)->SetSize(FVector2D(OuterArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderLeft1->Slot)->SetOffsets(FVector2D(0,YOffset));
		Cast<UCanvasPanelSlot>(BorderLeft1->Slot)->SetSize(FVector2D(InnerArea,YOffset));
		
		Cast<UCanvasPanelSlot>(BorderBottom->Slot)->SetOffsets(FVector2D(XOffset,-OuterArea));
		Cast<UCanvasPanelSlot>(BorderBottom->Slot)->SetPosition(FVector2D(XOffset,-InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottom1->Slot)->SetOffsets(FVector2D(XOffset,-InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottom1->Slot)->SetPosition(FVector2D(XOffset,0));

		Cast<UCanvasPanelSlot>(BorderRight->Slot)->SetOffsets(FVector2D(-InnerArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderRight->Slot)->SetSize(FVector2D(-OuterArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderRight1->Slot)->SetOffsets(FVector2D(0,YOffset));
		Cast<UCanvasPanelSlot>(BorderRight1->Slot)->SetSize(FVector2D(-InnerArea,YOffset));
	}

	if(BorderTopLeftX && BorderTopLeftY && BorderTopRightX && BorderTopRightY && BorderBottomLeftX && BorderBottomLeftY && BorderBottomRightX && BorderBottomRightY)
	{
		Cast<UCanvasPanelSlot>(BorderTopLeftX->Slot)->SetOffsets(FVector2D(XOffset,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopLeftX->Slot)->SetPosition(FVector2D(0,0));
		Cast<UCanvasPanelSlot>(BorderTopRightX->Slot)->SetOffsets(FVector2D(-XOffset,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopRightX->Slot)->SetPosition(FVector2D(0,0));

		Cast<UCanvasPanelSlot>(BorderTopLeftY->Slot)->SetOffsets(FVector2D(0,0));
		Cast<UCanvasPanelSlot>(BorderTopLeftY->Slot)->SetSize(FVector2D(InnerArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderBottomLeftY->Slot)->SetOffsets(FVector2D(0, -YOffset));
		Cast<UCanvasPanelSlot>(BorderBottomLeftY->Slot)->SetSize(FVector2D(InnerArea,YOffset));
		
		Cast<UCanvasPanelSlot>(BorderBottomLeftX->Slot)->SetOffsets(FVector2D(XOffset,-InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottomLeftX->Slot)->SetPosition(FVector2D(0,0));
		Cast<UCanvasPanelSlot>(BorderBottomRightX->Slot)->SetOffsets(FVector2D(-XOffset,-InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottomRightX->Slot)->SetPosition(FVector2D(0,0));

		Cast<UCanvasPanelSlot>(BorderTopRightY->Slot)->SetOffsets(FVector2D(0,0));
		Cast<UCanvasPanelSlot>(BorderTopRightY->Slot)->SetSize(FVector2D(-InnerArea,YOffset));
		Cast<UCanvasPanelSlot>(BorderBottomRightY->Slot)->SetOffsets(FVector2D(0,-YOffset));
		Cast<UCanvasPanelSlot>(BorderBottomRightY->Slot)->SetSize(FVector2D(-InnerArea,YOffset));
	}
	
	if(BorderTopLeftYOuter && BorderTopLeftXOuter && BorderTopRightYOuter && BorderTopRightXOuter && BorderBottomLeft && BorderBottomRight)
	{
		Cast<UCanvasPanelSlot>(BorderTopLeftYOuter->Slot)->SetOffsets(FVector2D(OuterArea,YOffset-InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopLeftYOuter->Slot)->SetPosition(FVector2D(InnerArea,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopLeftXOuter->Slot)->SetOffsets(FVector2D(XOffset-OuterArea-InnerArea,OuterArea));
		Cast<UCanvasPanelSlot>(BorderTopLeftXOuter->Slot)->SetPosition(FVector2D(OuterArea+InnerArea,InnerArea));
		
		Cast<UCanvasPanelSlot>(BorderTopRightYOuter->Slot)->SetOffsets(FVector2D(-OuterArea,YOffset-InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopRightYOuter->Slot)->SetPosition(FVector2D(-InnerArea,InnerArea));
		Cast<UCanvasPanelSlot>(BorderTopRightXOuter->Slot)->SetOffsets(FVector2D(-(XOffset-OuterArea-InnerArea),OuterArea));
		Cast<UCanvasPanelSlot>(BorderTopRightXOuter->Slot)->SetPosition(FVector2D(-(OuterArea+InnerArea),InnerArea));
		
		Cast<UCanvasPanelSlot>(BorderBottomLeft->Slot)->SetOffsets(FVector2D(XOffset-InnerArea,-YOffset+InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottomLeft->Slot)->SetPosition(FVector2D(InnerArea,-InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottomRight->Slot)->SetOffsets(FVector2D(-XOffset+InnerArea,-YOffset+InnerArea));
		Cast<UCanvasPanelSlot>(BorderBottomRight->Slot)->SetPosition(FVector2D(-InnerArea,-InnerArea));

	}
	
}

