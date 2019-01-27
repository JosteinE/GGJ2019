// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GGJ2019Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ItemBase.h"

//////////////////////////////////////////////////////////////////////////
// AGGJ2019Character

AGGJ2019Character::AGGJ2019Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

/*
UItemBase * AGGJ2019Character::getItem(int32 index)
{
	if (index < inventory.Num() && index >= 0) {
		return inventory[index];
	}
	return nullptr;
}

void AGGJ2019Character::Equip(int32 index)
{
	UItemBase* item = getItem(index);
	if (item != nullptr) {
		currentlyEquipped = item;
	}
}
*/

//////////////////////////////////////////////////////////////////////////
// Input

void AGGJ2019Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGGJ2019Character::IsJumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AGGJ2019Character::IsNotJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGGJ2019Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGGJ2019Character::MoveRight);


	PlayerInputComponent->BindAction("LeftMouseB", IE_Pressed, this, &AGGJ2019Character::LeftMouseBDown);
	PlayerInputComponent->BindAction("LeftMouseB", IE_Released, this, &AGGJ2019Character::LeftMouseBUp);

	PlayerInputComponent->BindAction("Key1", IE_Pressed, this, &AGGJ2019Character::key1);
	PlayerInputComponent->BindAction("Key2", IE_Pressed, this, &AGGJ2019Character::key2);
	PlayerInputComponent->BindAction("Key3", IE_Pressed, this, &AGGJ2019Character::key3);
	PlayerInputComponent->BindAction("Key4", IE_Pressed, this, &AGGJ2019Character::key4);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGGJ2019Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGGJ2019Character::LookUpAtRate);

	// handle touch devices
	//PlayerInputComponent->BindTouch(IE_Pressed, this, &AGGJ2019Character::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &AGGJ2019Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AGGJ2019Character::OnResetVR);
}


void AGGJ2019Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AGGJ2019Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AGGJ2019Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AGGJ2019Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGGJ2019Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGGJ2019Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGGJ2019Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AGGJ2019Character::IsJumping()
{
	//bIsJumping = true;
	//Jump();
}

void AGGJ2019Character::IsNotJumping()
{
	//bIsJumping = false;
}

void AGGJ2019Character::LeftMouseBDown()
{
	bLeftMouseBDown = true;
	bSwingingCurrent = true;
}

void AGGJ2019Character::LeftMouseBUp()
{
	bLeftMouseBDown = false;
	bSwingingCurrent = false;
}

void AGGJ2019Character::key1()
{
	if (bUnlockedAxe)
	{
		resetKeys();
		bUsingAxe = true;
	}
}

void AGGJ2019Character::key2()
{
	if (bUnlockedTorch)
	{
		resetKeys();
		bUsingTorch = true;
	}
}

void AGGJ2019Character::key3()
{
	if (bUnlockedSpade)
	{
		resetKeys();
		bUsingSpade = true;
	}
}

void AGGJ2019Character::key4()
{
	if (bUnlockedKey)
	{
		resetKeys();
		bUsingKey = true;
	}
}

void AGGJ2019Character::resetKeys()
{
	bUsingAxe = false;
	bUsingTorch = false;
	bUsingSpade = false;
	bUsingKey = false;
}