// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "World/Structures/MasterStructureAsset.h"

#include "BuildingButton.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API UBuildingButton final : public UButton
{
	GENERATED_BODY()

public:

	UBuildingButton();	
	virtual void PostLoad() override;
	
	UFUNCTION()
		void LoadStyle();

	UFUNCTION()
		void SetBpPath(const FSoftClassPath Path);

	UFUNCTION()
		TSubclassOf<class AMasterStructureAsset> GetBuildingClass();

	UFUNCTION()
		void SetActive(const bool Active);

	UFUNCTION()
		bool GetActive() const;
protected:
	
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<class AMasterStructureAsset> BuildingClass;
	
	UPROPERTY(BlueprintReadOnly)
	FSoftClassPath BpPath;

	UPROPERTY(BlueprintReadOnly)
	bool bActive;
	
};
