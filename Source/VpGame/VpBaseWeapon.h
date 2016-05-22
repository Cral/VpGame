#pragma once

#include "GameFramework/Actor.h"
#include "VpBaseWeapon.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS( config = Game )
class AVpBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AVpBaseWeapon();

	void OnStartFiring();
	void OnStopFiring();

	virtual void Tick( float DeltaSeconds ) override;

protected:
	void ShotTimerExpired();
	void TryFiring();

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Weapon )
	TSubclassOf<class AVpProjectile> ProjectileClass;

	UPROPERTY( Category = Audio, EditAnywhere, BlueprintReadWrite )
	class USoundBase* FireSound;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	float FireRate;

	bool bIsFiring = false;
	bool bCanFire = true;

	FTimerHandle TimerHandle_ShotTimerExpired;
};

