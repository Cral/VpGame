#include "VpGame.h"
#include "VpEnemy.h"
//#include "GameFramework/ProjectileMovementComponent.h"

AVpEnemy::AVpEnemy()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh0"));
	EnemyMesh->SetStaticMesh(EnemyMeshAsset.Object);
	EnemyMesh->AttachTo(RootComponent);
	EnemyMesh->BodyInstance.SetCollisionProfileName("Enemy");
	//EnemyMesh->OnComponentHit.AddDynamic(this, &AVpProjectile::OnHit);
	RootComponent = EnemyMesh;

// 	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
// 	ProjectileMovement->UpdatedComponent = ProjectileMesh;
// 	ProjectileMovement->InitialSpeed = 3000.f;
// 	ProjectileMovement->MaxSpeed = 3000.f;
// 	ProjectileMovement->bRotationFollowsVelocity = true;
// 	ProjectileMovement->bShouldBounce = false;
// 	ProjectileMovement->ProjectileGravityScale = 0.f;
// 
// 	InitialLifeSpan = 3.0f;
}

float AVpEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Destroy();
	}

	return DamageAmount;
}