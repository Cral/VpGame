#pragma once

#include "GameFramework/Actor.h"
#include "VpEnemy.generated.h"

//class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class AVpEnemy : public AActor
{
	GENERATED_BODY()

public:
	AVpEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	//FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	UStaticMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float Health = 100.0f;
};

