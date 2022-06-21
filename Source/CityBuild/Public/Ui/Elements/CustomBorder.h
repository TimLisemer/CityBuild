// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "CustomBorder.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API UCustomBorder : public UBorder
{
	GENERATED_BODY()

public:

	UCustomBorder();
	virtual void SynchronizeProperties() override;
	bool IsActive() const;

private:

	void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	void OnMouseLeave(const FPointerEvent& MouseEvent);

	UPROPERTY()
	bool bActive;

	
};
