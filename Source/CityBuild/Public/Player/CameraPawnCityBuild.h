// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#pragma once

#include "CoreMinimal.h"
#include "CameraPawnCityBuild.generated.h"

UCLASS()
class CITYBUILD_API ACameraPawnCityBuild final : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawnCityBuild();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Camera Movement Component
	UPROPERTY(Category = "Movement Compomemt", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAcess = "true"))
		class UCameraMovementComponent* PawnMovementComponent;
	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;
	
// Attributes
protected:
	
	/** Collision Sphere and root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RootComp")
		class USphereComponent* CollisionSphere;

	/** Player Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		class UCameraComponent* PlayerCamera;

	/** SpringArm or CameraArm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
		class USpringArmComponent* CameraArm;

	/** Default CameraArm Length */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
		float DefaultZoomLength;

	/** Default Rotation */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
		FRotator DefaultCameraRotation;

public:
	//Getters
	/** Returns Camera */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Getters")
		UCameraComponent* GetCamera() const { return PlayerCamera; }

	/** Returns Length of CameraArm */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Camera Zoom")
		float GetCurrentArmLength() const;
	

	// FOV here

	// Setters
	UFUNCTION(BlueprintCallable, Category="Camera Zoom")
		void ChangeArmLength(float ChangeAmount) const;

	UFUNCTION(BlueprintCallable, Category="Camera Zoom")
		void SetArmRotation(FRotator ChangeAmount) const;

	UFUNCTION(BlueprintCallable, Category="Camera Zoom")
		void SetToDefaultZoom() const;

	// FOV here

	
	
};
