// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "F3_Information.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API UF3_Information final : public UUserWidget
{
	GENERATED_BODY()
	
public:
	explicit UF3_Information(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	// Camera Speed
	void UpdateCameraSpeed(const float SpeedX, const float SpeedY, const FLinearColor Color) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* CameraSpeedX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* CameraSpeedY;

	// Spare Variables
	UPROPERTY()
		TArray<UTextBlock*> TextBlocks;
	UFUNCTION()
		void SetSpareVariables(const int32 TextBlocksSlot, const FString Description, const FString Variable);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable13;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable14;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) //Important: BindWidget
		class UTextBlock* SpareVariable15;

};
