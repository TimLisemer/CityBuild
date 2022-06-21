// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API UPauseMenu final: public UUserWidget
{
	GENERATED_BODY()

public:

	explicit UPauseMenu(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
		void Continue();

	UFUNCTION()
		void MainMenu();

	UFUNCTION()
		void Exit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BContinue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BMainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BExit;
	
};
