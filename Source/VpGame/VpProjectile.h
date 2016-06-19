#pragma once

#include "GameFramework/Actor.h"
#include "VpProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class AVpProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AVpProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* SomeComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Damage )
	TSubclassOf<class UDamageType> DamageTypeClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Effects )
	class UParticleSystem* ImpactEffect;
};

