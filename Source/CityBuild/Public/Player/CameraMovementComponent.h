// Author: Tim Lisemer - Tim.Lisemer@gmx.de
#pragma once

#include "CoreMinimal.h"
#include "Player/CityBuildPlayerController.h"
#include "CameraMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CITYBUILD_API UCameraMovementComponent final: public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Get Attached Pawn */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		ACameraPawnCityBuild* CameraOwner;

	/** Character Controller Reference */
	UPROPERTY(BlueprintReadWrite)
		ACityBuildPlayerController* PlayerController;

protected:
	// Attributes

	// Booleans

	/** Is Movement Disabled? */
	UPROPERTY(Category = "movement Variables: Bools", BlueprintReadOnly)
		bool bDisableCameraMovement;

	/** Is Movement Speed Modifier Active? */
	UPROPERTY(Category = "movement Variables: Bools", BlueprintReadOnly)
		bool bMovementSpeedModifierActive;
	
	// Movement Speeds
	/** Default Camera Speed */
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float DefaultMovementSpeed;

	/** Modifies the default Movement Speed when Called */
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float MovementSpeedModifier;

	/** Current Camera X Speed */
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float CurrentCameraSpeedX;

	/** Current Camera Y Speed */
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		float CurrentCameraSpeedY;

	// Camera Direction
	/** Gets Forward Direction of Camera Pawn */
	UPROPERTY(Category = "movement Variables: Movement Speeds", BlueprintReadOnly)
		FVector FaceDirection;

	// Zoom
	/** Default CameraArmLength */
	UPROPERTY(Category = "movement Variables: Zoom", BlueprintReadOnly)
		float DefaultZoomLength;

	/** Amount Camera Arm Changes */
	UPROPERTY(Category = "movement Variables: Zoom", BlueprintReadOnly)
		float DeltaArm;

	/** Amount the Rotation Changes */
	UPROPERTY(Category = "movement Variables: Zoom", BlueprintReadOnly)
		FRotator DeltaRotation;

	/** Farthest Camera can get on zoom out */
	UPROPERTY(Category = "movement Variables: Zoom", BlueprintReadOnly)
		float MaxZoom;

	/** Closest Camera can get on zoom out */
	UPROPERTY(Category = "movement Variables: Zoom", BlueprintReadOnly)
		float MinZoom;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
		class ACityBuildHud* CityBuildHud;

public:
	// methods

	// Getters

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
		FORCEINLINE float GetDefaultMovementSpeed() const { return DefaultMovementSpeed; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
		FORCEINLINE float GetSpeedModifier() const { return MovementSpeedModifier; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
		FORCEINLINE bool GetSpeedModifierActive() const { return bMovementSpeedModifierActive; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
		FORCEINLINE bool IsCameraDisabled() const { return bDisableCameraMovement; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Location")
		FVector GetCameraLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Direction")
	FRotator GetCameraRotation() const;

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
		float SetDefaultMovementSpeedModifier(const float ModifierAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
		bool SetMovementSpeedModifierActive(bool Active);

	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
		float SetDefaultMovementSpeed(const float MovementSpeedAdjustment);

	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
		bool SetCameraDisable(const bool DisableCamera);

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void BasicMovementControl(const float AxisValueX,const float AxisValueY);

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void PanCamera(const float RotationAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void ResetPan() const;

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
		void EdgeScroll();

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
		void ZoomIn() const;

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
		void ZoomOut() const;
	
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
		void DefaultZoom() const;

	bool MouseSpeedActive = false;
};
