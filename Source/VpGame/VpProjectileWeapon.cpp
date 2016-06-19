#include "VpGame.h"
#include "VpProjectileWeapon.h"

AVpProjectileWeapon::AVpProjectileWeapon() : AVpBaseWeapon()
{
}

void AVpProjectileWeapon::Fire( const FVector& FireDirection )
{
	const AActor* const Barrel = GetNextBarrel();
	UWorld* const World = GetWorld();

	if( World && Barrel )
	{
		AVpProjectile* Projectile = World->SpawnActor<AVpProjectile>( ProjectileClass, Barrel->GetActorLocation(), FireDirection.Rotation() );
		World->GetTimerManager().SetTimer( TimerHandle_ShotTimerExpired, this, &AVpBaseWeapon::ShotTimerExpired, FireRate );

		if( FireSound != nullptr )
		{
			UGameplayStatics::PlaySoundAtLocation( this, FireSound, GetActorLocation() );	
		}

		SpawnMuzzleEffect( World, Barrel );
	}
}