// Copyright Epic Games, Inc. All Rights Reserved.

#include "GripTaskCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "GripTask/GameModes/GripTaskGameplayMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AGripTaskCharacter::AGripTaskCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));

	SetupMinimapCamera();
}

void AGripTaskCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	InitializeComponents();
}

void AGripTaskCharacter::InitializeComponents() const
{
	if (!AttributeComponent)
	{
		DEBUG_PRINT("AttributeComponent not set");
	}
	else
	{
		SetupCharacterStats(AttributeComponent->GetCharacterStatsId());
	}

	if (!TargetComponent)
	{
		DEBUG_PRINT("TargetComponent not set");
	}
	else
	{
		TargetComponent->SetPlayerController(Cast<APlayerController>(GetController()));
	}
}

bool AGripTaskCharacter::IsTarget() const
{
	return true;
}

UTargetComponent* AGripTaskCharacter::GetActorTargetComponent()
{
	return TargetComponent;
}

UAttributeComponent* AGripTaskCharacter::GetAttributeComponent()
{
	return AttributeComponent;
}

/**
 * @brief Custom jump implementation that is extended by mana consumption, prevents jumping if not enough mana
 */
void AGripTaskCharacter::JumpImpl()
{
	if (AttributeComponent->GetMana() > 25.f)
	{
		Super::Jump();
		if (!GetCharacterMovement()->IsFalling())
			AttributeComponent->ConsumeMana(25.f);
	}
	else
	{
		DEBUG_PRINT("Not enough mana to jump");
	}
}

void AGripTaskCharacter::SetupMinimapCamera()
{
	MinimapCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MinimapCameraBoom"));
	MinimapCameraBoom->SetupAttachment(RootComponent);
	MinimapCameraBoom->TargetArmLength = 500.0f;
	MinimapCameraBoom->bUsePawnControlRotation = true;
	MinimapCameraBoom->bInheritPitch = false;
	MinimapCameraBoom->bInheritYaw = false;
	MinimapCameraBoom->bInheritRoll = false;
	MinimapCameraBoom->bDoCollisionTest = false;
	MinimapCameraBoom->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	MinimapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapCapture"));
	MinimapCapture->SetupAttachment(MinimapCameraBoom, USpringArmComponent::SocketName);
	MinimapCapture->PostProcessBlendWeight = 0.0f;
	MinimapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	MinimapCapture->bCaptureEveryFrame = true;
	MinimapCapture->bCaptureOnMovement = true;
	MinimapCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;

	MinimapCapture->ShowFlags.SetAntiAliasing(false);
	MinimapCapture->ShowFlags.SetAtmosphere(false);
	MinimapCapture->ShowFlags.SetBSP(false);
	MinimapCapture->ShowFlags.SetDecals(false);
	MinimapCapture->ShowFlags.SetFog(false);
	MinimapCapture->ShowFlags.SetGrid(false);
	MinimapCapture->ShowFlags.SetParticles(false);
	MinimapCapture->ShowFlags.SetSkeletalMeshes(false);
	MinimapCapture->ShowFlags.SetLighting(false);
	MinimapCapture->ShowFlags.SetTranslucency(false);
	MinimapCapture->ShowFlags.SetPostProcessing(false);
	MinimapCapture->ShowFlags.SetSkyLighting(false);
	MinimapCapture->ShowFlags.SetDynamicShadows(false);
	MinimapCapture->ShowFlags.SetVolumetricFog(false);

	MinimapCapture->ShowFlags.SetStaticMeshes(true);
	MinimapCapture->ShowFlags.SetLandscape(true);
	MinimapCapture->ShowFlags.SetInstancedFoliage(true);
	MinimapCapture->ShowFlags.SetInstancedGrass(true);
	MinimapCapture->ShowFlags.SetInstancedStaticMeshes(true);

	MinimapCapture->HiddenActors.Add(this);
	MinimapCapture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;
}

void AGripTaskCharacter::Jump()
{
	JumpImpl();
}

void AGripTaskCharacter::LeftMouseClicked(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		DEBUG_PRINT("Left mouse clicked");
		if(TargetComponent)
			TargetComponent->LeftMouseClicked();
	}
}

void AGripTaskCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGripTaskCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGripTaskCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGripTaskCharacter::Look);
		EnhancedInputComponent->BindAction(LeftMouseClickAction, ETriggerEvent::Triggered, this,
		                                   &AGripTaskCharacter::LeftMouseClicked);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AGripTaskCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGripTaskCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		// Rotate the minimap camera
		MinimapCapture->SetWorldRotation(FRotator(-90.0f, GetControlRotation().Yaw, 0.0f));
	}
}

void AGripTaskCharacter::SetupCharacterStats(const FName Id) const
{
	if (const AGripTaskGameplayMode* GameMode = Cast<AGripTaskGameplayMode>(GetWorld()->GetAuthGameMode()))
	{
		if (FCharacterStats* Stats = GameMode->GetCharacterStats(Id))
		{
			AttributeComponent->SetBaseStats(Stats);
		}
	}
}
