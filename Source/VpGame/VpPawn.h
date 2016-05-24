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

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
	float StrafeSpeed;

	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
	float ClimbSpeed;

	// Begin Actor Interface
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;
	// End Actor Interface

	void Move( float DeltaSeconds );

	// Static names for axis bindings
	static const FName MoveUpBinding;
	static const FName MoveRightBinding;

protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Weapon )
	TSubclassOf<class AVpBaseWeapon> PrimaryWeaponClass;

private:
	class AVpBaseWeapon* PrimaryWeapon;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
