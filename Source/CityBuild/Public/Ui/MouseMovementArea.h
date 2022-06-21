// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Elements/CustomBorder.h"
#include "MouseMovementArea.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API UMouseMovementArea final: public UUserWidget
{
	GENERATED_BODY()

public:

	explicit UMouseMovementArea(const FObjectInitializer& ObjectInitializer);

	bool SetBorderVisibility(const bool Visible);
	bool GetVisibility() const;

	virtual void NativeConstruct() override;

	
	//Mouse Movement Area
	
	UPROPERTY()
		TArray<UCustomBorder*> Borders;

	UPROPERTY()
		bool bVisibility;
	
	UFUNCTION()
		void SetMouseMovementAreas(const float InnerArea, const float OuterArea, const float XOffset, const float YOffset) const;

	//Normal Border
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderTop1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderLeft1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderRight1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderBottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UCustomBorder* BorderBottom1;

	//Outer Corner Border
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopLeftYOuter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopLeftXOuter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopRightYOuter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopRightXOuter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomRight;

	//Inner Corner Border
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopLeftX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopLeftY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopRightX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderTopRightY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomLeftX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomLeftY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomRightX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
	class UCustomBorder* BorderBottomRightY;

};
