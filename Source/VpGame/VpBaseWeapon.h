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

	void Initialize( UStaticMeshComponent* ShipMesh );

	void OnStartFiring();
	void OnStopFiring();

	virtual void Tick( float DeltaSeconds ) override;

	const FVector& GetPositionOffset() { return PositionOffset; }

protected:
	void ShotTimerExpired();
	void TryFiring();

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	TSubclassOf<class AVpProjectile> ProjectileClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	TSubclassOf<class AActor> BarrelClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Audio )
	class USoundBase* FireSound;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	TArray<FName> BarrelSocketNames;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	float FireRate;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	FVector PositionOffset;

	bool bIsFiring = false;
	bool bCanFire = true;

	int32 BarrelIndex = 0;

	TArray<AActor*> Barrels;

	FTimerHandle TimerHandle_ShotTimerExpired;
};

