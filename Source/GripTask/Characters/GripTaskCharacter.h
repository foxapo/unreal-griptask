// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GripTask/Interfaces/AttributeInterface.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "Logging/LogMacros.h"
#include "GripTaskCharacter.generated.h"

struct FCharacterStats;
struct FInputActionValue;
class UAttributeComponent;
class UTargetComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AGripTaskGameplayMode;
class USceneCaptureComponent2D;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGripTaskCharacter : public ACharacter, public ITargetInterface, public IAttributeInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftMouseClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleQuestAction;

	/* MINIMAP */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* MinimapCameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* MinimapCapture;

	/* ATTRIBUTE COMPONENT */
	UPROPERTY(VisibleAnywhere, Transient)
	UAttributeComponent* AttributeComponent;
	/* ACTOR TARGET COMPONENT */
	UPROPERTY(VisibleAnywhere, Transient)
	UTargetComponent* TargetComponent;

public:
	AGripTaskCharacter();
	virtual bool IsTarget() override;
	virtual UTargetComponent* GetActorTargetComponent() override;
	virtual UAttributeComponent* GetAttributeComponent() override;
	virtual void SetupCharacterStats(FName Id) override;
	void ToggleQuestLog();

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Jump() override;
	virtual void LeftMouseClicked(const FInputActionValue& Value);
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE USpringArmComponent* GetMinimapCameraBoom() const { return MinimapCameraBoom; }
	FORCEINLINE USceneCaptureComponent2D* GetMinimapCamera() const { return MinimapCapture; }

protected:
	void JumpImpl();
	void SetupMinimapCamera();
};
