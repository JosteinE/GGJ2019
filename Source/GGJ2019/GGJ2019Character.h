// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGJ2019Character.generated.h"

// Forward declarations
class UItemBase;

UCLASS(config=Game)
class AGGJ2019Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AGGJ2019Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//UItemBase* getItem(int32 index);

	//// UFUNCTION(BlueprintCallable)
	//void Equip(int32 index);


	//TArray<UItemBase*> inventory;

protected:
	// The currently equipped item
	// UItemBase *currentlyEquipped = nullptr;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerHealth = 100;

	//Items unlocked
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedAxe = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedTorch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedSpade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUnlockedKey = false;

	//Swinging current
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwingingCurrent = false;

	//Item selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsingAxe = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsingTorch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsingSpade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsingKey = false;

	//Input variables
	bool bIsJumping;
	bool bLeftMouseBDown;

	//Input functions
	void LeftMouseBDown();
	void LeftMouseBUp();
	void key1();
	void key2();
	void key3();
	void key4();
	void IsJumping();
	void IsNotJumping();

	void resetKeys();
};
