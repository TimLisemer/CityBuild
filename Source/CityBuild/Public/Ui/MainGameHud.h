// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Elements/BuildingButton.h"

#include "MainGameHud.generated.h"

class ACityBuildPlayerController;
/**
 * 
 */
UCLASS()
class CITYBUILD_API UMainGameHud final : public UUserWidget
{
	GENERATED_BODY()

public:

	explicit UMainGameHud(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	//Top Right
	UFUNCTION()
		void SetTime(const FString Time) const;
protected:
	UFUNCTION()
		void OpenPauseMenu();
	UFUNCTION()
		void Speed1();
	UFUNCTION()
		void Speed2();
	UFUNCTION()
		void Speed3();
	UFUNCTION()
		void Speed4();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BOpenPauseMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BSpeed1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BSpeed2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BSpeed3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* BSpeed4;

	//Top Left
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TimeBlock;

	//Bottom
public:
	UFUNCTION()
		void ManageButtons();
	UFUNCTION()
		void BuildButtonOnClick(UBuildingButton* Button);

	UFUNCTION()
		static void BuildButtonHover(const UBuildingButton* Button);
	
	UFUNCTION()
		void SetActiveBuildButton(UBuildingButton* Button, const bool NewActiveStatus);

	UPROPERTY(BlueprintReadOnly)
		UBuildingButton* ActiveBuildButton = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton11;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UBuildingButton* BuildingButton12;
protected:

	UFUNCTION()
		void BuildButtonHover1();

	UFUNCTION()
		void BuildButtonHover2();

	UFUNCTION()
		void BuildButtonHover3();

	UFUNCTION()
		void BuildButtonHover4();

	UFUNCTION()
		void BuildButtonHover5();

	UFUNCTION()
		void BuildButtonHover6();

	UFUNCTION()
		void BuildButtonHover7();

	UFUNCTION()
		void BuildButtonHover8();

	UFUNCTION()
		void BuildButtonHover9();

	UFUNCTION()
		void BuildButtonHover10();

	UFUNCTION()
		void BuildButtonHover11();

	UFUNCTION()
		void BuildButtonHover12();
	

	UFUNCTION()
		void BuildButton1();
	UFUNCTION()
		void BuildButton2();
	UFUNCTION()
		void BuildButton3();
	UFUNCTION()
		void BuildButton4();
	UFUNCTION()
		void BuildButton5();
	UFUNCTION()
		void BuildButton6();
	UFUNCTION()
		void BuildButton7();
	UFUNCTION()
		void BuildButton8();
	UFUNCTION()
		void BuildButton9();
	UFUNCTION()
		void BuildButton10();
	UFUNCTION()
		void BuildButton11();
	UFUNCTION()
		void BuildButton12();

	UPROPERTY(BlueprintReadWrite)
		ACityBuildPlayerController* PlayerController;
};
