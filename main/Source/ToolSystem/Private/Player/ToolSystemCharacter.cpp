// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ToolSystemCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ToolSystem.h"
#include "MinigameSystem/Widgets/ElectricalFixWidget.h"

AToolSystemCharacter::AToolSystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AToolSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AToolSystemCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AToolSystemCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AToolSystemCharacter::Look);
	
		// Tools
		EnhancedInputComponent->BindAction(ToolsAction, ETriggerEvent::Started, this, &AToolSystemCharacter::OnToolInput);
	}
	else
	{
		UE_LOG(LogToolSystem, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AToolSystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AToolSystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AToolSystemCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AToolSystemCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AToolSystemCharacter::OnToolInput(const FInputActionValue& Value)
{
	float ToolIndex = Value.Get<float>();
	
	if (ToolIndex == 5.0f)
	{
		if (!EquippedTool) return;
		EquippedTool->StartTool();
		return;
	}
	else if (ToolIndex == 6.0f) // space for skill check
	{
		if (!EquippedTool) return;
		if (!(EquippedTool->MinigameInstance)) return;
		UElectricalFixWidget* ElectricalWidget = Cast<UElectricalFixWidget>(EquippedTool->MinigameInstance->MinigameWidgetInstance);
		ElectricalWidget->TriggerSkillCheck();
		return;
	}
	else if (ToolIndex == 7.0f) // esc for cancel
	{
		if (!EquippedTool) return;
		if (!(EquippedTool->MinigameInstance)) return;
		EquippedTool->MinigameInstance->CancelMinigame();
		return;
	}
	EquipTool(ToolClasses[ToolIndex-1]);
}

void AToolSystemCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AToolSystemCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

//=============================================================
//						CUSTOM FUNCTIONS
//=============================================================

void AToolSystemCharacter::EquipTool(const TSubclassOf<AToolBase>& Tool)
{
	if (EquippedTool && EquippedTool->GetClass() == Tool) return;
	if (EquippedTool)
	{
		EquippedTool->Destroy();
		EquippedTool = nullptr;
	}
	if (!Tool) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	EquippedTool = GetWorld()->SpawnActor<AToolBase>(Tool, GetActorTransform(), SpawnParams);
	
	EquippedTool->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquippedTool->SocketName);
	EquippedTool->Initialize(ToolDataTable);
}