// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"

#include "VpPawn.generated.h"

UCLASS(Blueprintable)
class AVpPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	AVpPawn();

	/** Offset from the ships location to spawn projectiles */
	//UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	//FVector GunOffset;
	
	/* How fast the weapon will fire */
	//UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	//float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	/** Sound to play each time we fire */
	//UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	//class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;
	// End Actor Interface

	void Move( float DeltaSeconds );
	void FireShot();

	/* Handler for the fire timer expiry */
	//void ShotTimerExpired();

	//void FirePrimaryWeaponStart();
	//void FirePrimaryWeaponStop();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Weapon )
	TSubclassOf<class AVpBaseWeapon> PrimaryWeaponClass;

private:

	/* Flag to control firing  */
	//uint32 bCanFire : 1;

	uint32 bIsFiring : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	//FTimerHandle TimerHandle_ShotTimerExpired;

	class AVpBaseWeapon* PrimaryWeapon;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};

