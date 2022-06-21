// Author: Tim Lisemer - Tim.Lisemer@gmx.de

#include "Player/CameraPawnCityBuild.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/CameraMovementComponent.h"

// Sets default values
ACameraPawnCityBuild::ACameraPawnCityBuild()
{
	//Set Defaults
	DefaultZoomLength = 1350.0f;
	DefaultCameraRotation = FRotator(-75.0, 0.0, 0.0); //Pitch (Y), Yaw(Z), Roll (X)
	//FOV here

	// Set Root Component and also set root Components size.
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(32.0);
	CollisionSphere->SetWorldScale3D(FVector(0.25, 0.25, 0.25));
	// The Collision Profile Name - Used for map boundaries

	// Default Settings for inheriting controller rotations
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create Camera arm and attach to Root
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bUsePawnControlRotation = false;
	CameraArm->TargetArmLength = DefaultZoomLength;
	CameraArm->SetRelativeRotation(DefaultCameraRotation);
	CameraArm->bDoCollisionTest = false;
	CameraArm->bEnableCameraLag = true; //Smoother Movements
	CameraArm->bEnableCameraRotationLag = true;
	CameraArm->bInheritPitch = false; // needs to be false for zoom to update in realtime


	//Collision
	CollisionSphere->SetGenerateOverlapEvents(false);
	bGenerateOverlapEventsDuringLevelStreaming = false;
	
	// Create Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	// FOV here
	
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// Attach Movement Component
	PawnMovementComponent = CreateDefaultSubobject<UCameraMovementComponent>(TEXT("CameraPawnMovementComponent"));
	if(!PawnMovementComponent){
		UE_LOG(LogTemp, Error, TEXT("Error Creating PawnMovementComponent"));
	}

}

// Called when the game starts or when spawned
void ACameraPawnCityBuild::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Camera Pawn Started")));
}

// Called every frame
void ACameraPawnCityBuild::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACameraPawnCityBuild::GetCurrentArmLength() const
{
	return CameraArm->TargetArmLength;
}

void ACameraPawnCityBuild::ChangeArmLength(float const ChangeAmount) const
{
	CameraArm->TargetArmLength += ChangeAmount;
}

void ACameraPawnCityBuild::SetArmRotation(FRotator const ChangeAmount) const
{
	//Setting our min and max rotation amounts
	const FRotator RotationMax = FRotator(-25, 0.0, 0.0); //Zoom in Rotation Max
	const FRotator RotationMin = DefaultCameraRotation; //Zoom in Rotation Min --> same as DefaultRotation

	// Get 'x', the rotation change
	FRotator NewRotation = FRotator(CameraArm->GetRelativeRotation() + ChangeAmount);

	//Clamp the Pitch of NewRotation
	NewRotation = NewRotation.Pitch < RotationMin.Pitch ? RotationMin : NewRotation.Pitch < RotationMax.Pitch ? NewRotation : RotationMax;

	CameraArm->SetRelativeRotation(NewRotation); // CameraArm->RelativeRotation
}

void ACameraPawnCityBuild::SetToDefaultZoom() const
{
	CameraArm->TargetArmLength = DefaultZoomLength;
	CameraArm->SetRelativeRotation(DefaultCameraRotation);
}











