#pragma once

#include "VpBaseWeapon.h"
#include "VpInstantWeapon.generated.h"

UCLASS( config = Game )
class AVpInstantWeapon : public AVpBaseWeapon
{
	GENERATED_BODY()

public:
	AVpInstantWeapon();

	virtual void Fire( const FVector& FireDirection ) override;

	void SpawnImpactEffect( UWorld* World, const FVector& ImpactLocation, USceneComponent* OtherComp );
	void SpawnTrailEffect( UWorld* World, const FVector& StartLocation, const FVector& EndLocation );

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Damage )
	TSubclassOf<class UDamageType> DamageTypeClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Effects )
	class UParticleSystem* ImpactEffect;

	UPROPERTY( EditDefaultsOnly, Category = Effects )
	UParticleSystem* TrailEffect;

	UPROPERTY( EditDefaultsOnly, Category = Effects )
	FName TrailTargetParam;
};

