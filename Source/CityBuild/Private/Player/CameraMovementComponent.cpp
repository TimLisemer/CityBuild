// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "Player/CameraMovementComponent.h"
#include "Player/CityBuildPlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCameraMovementComponent::UCameraMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// Set Default attributes
	SetCameraDisable(false);
	SetDefaultMovementSpeedModifier(2.0f);
	SetDefaultMovementSpeed(30.0f);
	SetMovementSpeedModifierActive(false);
	DefaultZoomLength = 1350.0;
	DeltaArm = 150.0;
	DeltaRotation = FRotator(7.15, 0.0, 0.0);
	MinZoom = 9000.0;
	MaxZoom = 300;
}


// Called when the game starts
void UCameraMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Movement Component Started")));
	CameraOwner = Cast<ACameraPawnCityBuild>(GetOwner()); // populates the owner of this compo
	PlayerController =  Cast<ACityBuildPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // populates PlayerController
	CityBuildHud = Cast<ACityBuildHud>(PlayerController->GetHUD());
}


// Called every frame
void UCameraMovementComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!MouseSpeedActive)
	{
		if(GetSpeedModifierActive())
		{
			CityBuildHud->SetCameraSpeed(CurrentCameraSpeedX, CurrentCameraSpeedY, FLinearColor::Red);
		}else
		{
			CityBuildHud->SetCameraSpeed(CurrentCameraSpeedX, CurrentCameraSpeedY, FLinearColor::White);
		}
	}
}

// Methods
// Getters
FVector UCameraMovementComponent::GetCameraLocation() const
{
	return CameraOwner->GetActorLocation();
}

FRotator UCameraMovementComponent::GetCameraRotation() const
{
	return CameraOwner->GetActorRotation();
}


// Setters
float UCameraMovementComponent::SetDefaultMovementSpeedModifier(const float ModifierAmount)
{
	return MovementSpeedModifier = ModifierAmount;
}

bool UCameraMovementComponent::SetMovementSpeedModifierActive(const bool Active)
{
	return bMovementSpeedModifierActive = Active;
}

float UCameraMovementComponent::SetDefaultMovementSpeed(const float MovementSpeedAdjustment)
{
	return DefaultMovementSpeed = MovementSpeedAdjustment;
}

bool UCameraMovementComponent::SetCameraDisable(const bool DisableCamera)
{
	return bDisableCameraMovement = DisableCamera;
}

// Basic Movement Controls
/** Movement Control - W A S D*/
void UCameraMovementComponent::BasicMovementControl(const float AxisValueX,const float AxisValueY)
{
	// Calculate Zoom - Speed modifier
	const float ZoomMod = CameraOwner->GetCurrentArmLength() / MinZoom;
	
	if(!IsCameraDisabled())
	{
		// Set Variables used in movement calculation
		float SpeedX, SpeedY;
		if(GetSpeedModifierActive())
		{	
			SpeedX = AxisValueX * GetDefaultMovementSpeed() * ZoomMod * GetSpeedModifier();
			SpeedY = AxisValueY * GetDefaultMovementSpeed() * ZoomMod * GetSpeedModifier();
		}else
		{
			SpeedX = AxisValueX * GetDefaultMovementSpeed() * ZoomMod;
			SpeedY = AxisValueY * GetDefaultMovementSpeed() * ZoomMod;
		}
		if(AxisValueX != 0) CurrentCameraSpeedX = SpeedX;
		if(AxisValueY != 0) CurrentCameraSpeedY = SpeedY;
		
		FVector const Movement = FVector(SpeedX, SpeedY , 0);
		CameraOwner->AddActorLocalOffset(Movement, true);
	}
}

/** CameraPan */
void UCameraMovementComponent::PanCamera(const float RotationAmount) const
{	
	const FRotator NewRotation = GetCameraRotation().Add(0, RotationAmount, 0);
	CameraOwner->SetActorRotation(NewRotation);
}

/** Resets Camera Pan/Rotation */
void UCameraMovementComponent::ResetPan() const
{
	CameraOwner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

/** Edge Scroll X and Y are reversed on screen from the game world*/
void UCameraMovementComponent::EdgeScroll()
{
	// Variables for movement
	float SpeedX = 0.0f;
	float SpeedY = 0.0f;
	bool InnerSpeed = false;
	
	// Calculate Zoom - Speed modifier
	const float ZoomMod = CameraOwner->GetCurrentArmLength() / MinZoom;
	
	// Check if Speed Modifier can be applied
	//bool XSpeed = false;
	//bool YSpeed = false;

	// Get Viewport (play screen) size
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);


	// Calculate deltaResolution (Viewport = CurrentResolution but Widget Pixel = 1920*1080)
	float const OuterPixelX = ViewportSizeX / 100.0f * PlayerController->OuterMarginInPercent;
	float const InnerPixelX = ViewportSizeY / 100.0f * PlayerController->InnerMarginInPercent;
	CityBuildHud->SetMouseMovementAreas(InnerPixelX, OuterPixelX, 250, 200);

	const UMouseMovementArea* MouseMovement = CityBuildHud->MouseMovement;

	if(MouseMovement->BorderTopLeftYOuter->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = -GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderTopLeftXOuter->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = -GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderTopRightYOuter->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderTopRightXOuter->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderBottomLeft->IsActive())
	{
		SpeedY = -1.0f * GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = -GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderBottomRight->IsActive())
	{
		SpeedY = -1.0f * GetDefaultMovementSpeed() * ZoomMod;
		SpeedX = GetDefaultMovementSpeed() * ZoomMod;
	}

	if(MouseMovement->BorderTop1->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}
	if(MouseMovement->BorderBottom1->IsActive())
	{
		SpeedY = -1.0f * GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}
	if(MouseMovement->BorderLeft1->IsActive())
	{
		SpeedX = -GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}
	if(MouseMovement->BorderRight1->IsActive())
	{
		SpeedX = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}

	if(MouseMovement->BorderTopLeftX->IsActive() || MouseMovement->BorderTopLeftY->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		SpeedX = -GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}
	
	if(MouseMovement->BorderTopRightX->IsActive() || MouseMovement->BorderTopRightY->IsActive())
	{
		SpeedY = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		SpeedX = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}

	if(MouseMovement->BorderBottomLeftX->IsActive() || MouseMovement->BorderBottomLeftY->IsActive())
	{
		SpeedY = -1.0f * GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		SpeedX = -GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}

	if(MouseMovement->BorderBottomRightX->IsActive() || MouseMovement->BorderBottomRightY->IsActive())
	{
		SpeedY = -1.0f * GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		SpeedX = GetDefaultMovementSpeed() * GetSpeedModifier() * ZoomMod;
		InnerSpeed = true;
	}
	
	if(MouseMovement->BorderTop->IsActive()) SpeedY = GetDefaultMovementSpeed() * ZoomMod;
	if(MouseMovement->BorderBottom->IsActive()) SpeedY = -1.0f * GetDefaultMovementSpeed() * ZoomMod;
	if(MouseMovement->BorderLeft->IsActive()) SpeedX = -GetDefaultMovementSpeed() * ZoomMod;
	if(MouseMovement->BorderRight->IsActive()) SpeedX = GetDefaultMovementSpeed() * ZoomMod;

	

	const FVector Movement = FVector(SpeedY, SpeedX, 0.0f);	 // use with DeltaSpeedY;
	if(SpeedX == 0.0f && SpeedY == 0.0f)
	{
		MouseSpeedActive = false;
	}else
	{
		MouseSpeedActive = true;
		CurrentCameraSpeedX = SpeedX;
		CurrentCameraSpeedY = SpeedY;
		if(InnerSpeed)
		{
			CityBuildHud->SetCameraSpeed(CurrentCameraSpeedX, CurrentCameraSpeedY, FLinearColor::Blue);
		}else
		{
			CityBuildHud->SetCameraSpeed(CurrentCameraSpeedX, CurrentCameraSpeedY, FLinearColor::Green);
		}
	}
	CameraOwner->AddActorLocalOffset(Movement, true);

}

/** Zoom In*/
void UCameraMovementComponent::ZoomIn() const
{
	if (CameraOwner->GetCurrentArmLength() > MaxZoom)
	{
		CameraOwner->ChangeArmLength(-1.0f * DeltaArm);
		if (CameraOwner->GetCurrentArmLength() <= DefaultZoomLength)
		{
			CameraOwner->SetArmRotation(DeltaRotation);
		}
	}
}

/** Zoom Out*/
void UCameraMovementComponent::ZoomOut() const
{
	if (CameraOwner->GetCurrentArmLength() < MinZoom)
	{
		CameraOwner->ChangeArmLength(DeltaArm);
		if (CameraOwner->GetCurrentArmLength() <= DefaultZoomLength)
		{
			CameraOwner->SetArmRotation(-1.0f * DeltaRotation);
		}
	}
}

/** Set to default zoom*/
void UCameraMovementComponent::DefaultZoom() const
{
	CameraOwner->SetToDefaultZoom();
}

