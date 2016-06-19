#pragma once

#include "VpBaseWeapon.h"
#include "VpProjectile.h"
#include "VpProjectileWeapon.generated.h"

UCLASS( config = Game )
class AVpProjectileWeapon : public AVpBaseWeapon
{
	GENERATED_BODY()

public:
	AVpProjectileWeapon();

protected:
	virtual void Fire( const FVector& FireDirection ) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
	TSubclassOf<class AVpProjectile> ProjectileClass;
};

