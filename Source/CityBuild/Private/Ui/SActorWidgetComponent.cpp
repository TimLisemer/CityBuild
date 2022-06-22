#include "Ui/SActorWidgetComponent.h"
#include "UI/BuildingWidget.h"



USActorWidgetComponent::USActorWidgetComponent()
{
	// Set common defaults when using widgets on Actors
	SetDrawAtDesiredSize(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void USActorWidgetComponent::InitWidget()
{
	// Base implementation creates the 'Widget' instance
	Super::InitWidget();

	if (GetWidget())
	{
		if (!GetWidget()->IsA(UBuildingWidget::StaticClass()))
		{
			// Suggest deriving from actor widget (not strictly required, but you lose the benefit of auto-assigning the Actor this way)
			UE_LOG(LogTemp, Warning, TEXT("WidgetClass for %s does not derive from SActorWidget"), *GetNameSafe(GetOwner()));
		}
		if (UBuildingWidget* WidgetInst = Cast<UBuildingWidget>(GetWidget()))
		{
			// Assign the owner, now we have easy access in the widget itself
			WidgetInst->SetOwningActor(GetOwner());
		}
	}
}