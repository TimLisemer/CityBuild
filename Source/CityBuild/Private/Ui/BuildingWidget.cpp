// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/BuildingWidget.h"


UBuildingWidget::UBuildingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBuildingWidget::SetOwningActor(AActor* NewOwner)
{
	if (OwningActor == NewOwner)
	{
		// Skip repeated calls
		return;
	}

	OwningActor = NewOwner;

	OnOwningActorChanged.Broadcast(NewOwner);
}
