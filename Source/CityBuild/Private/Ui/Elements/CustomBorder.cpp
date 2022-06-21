// Author: Tim Lisemer - Tim.Lisemer@gmx.de


#include "UI/Elements/CustomBorder.h"

UCustomBorder::UCustomBorder()
{
	bActive = false;
}


void UCustomBorder::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	MyBorder->SetOnMouseEnter(BIND_UOBJECT_DELEGATE(FNoReplyPointerEventHandler, OnMouseEnter));
	MyBorder->SetOnMouseLeave(BIND_UOBJECT_DELEGATE(FSimpleNoReplyPointerEventHandler, OnMouseLeave));
}

bool UCustomBorder::IsActive() const
{
	return bActive;
}

void UCustomBorder::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	bActive = true;
	if(!MyBorder->IsHovered())
		MyBorder->OnMouseEnter(MyGeometry, MouseEvent);
}

void UCustomBorder::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	bActive = false;
	if(MyBorder->IsHovered())
		MyBorder->OnMouseLeave(MouseEvent);
}
