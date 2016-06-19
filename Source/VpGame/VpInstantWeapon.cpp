#include "VpGame.h"
#include "VpInstantWeapon.h"

AVpInstantWeapon::AVpInstantWeapon() : AVpBaseWeapon()
{
}

void AVpInstantWeapon::Fire( const FVector& FireDirection )
{
	Super::Fire( FireDirection );

	UWorld* const World = GetWorld();
	const AActor* const Barrel = GetNextBarrel();

	if( World && Barrel )
	{
		FHitResult HitInfo;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor( this );

		FCollisionObjectQueryParams ObjectParams;

		FVector HitStart = Barrel->GetActorLocation();
		FVector HitEnd = HitStart + FireDirection * 1500.0f;

		if( World->LineTraceSingleByChannel( HitInfo, HitStart, HitEnd, ECollisionChannel::ECC_WorldDynamic ) )
		{
			if( HitInfo.GetActor()->Tags.Contains( "BadDude" ) )
			{
				FDamageEvent DamageEvent( DamageTypeClass );

				const float DamageAmount = 60.0f;
				HitInfo.Actor->TakeDamage( DamageAmount, DamageEvent, NULL, this );
			}

			SpawnImpactEffect( World, HitInfo.ImpactPoint, HitInfo.GetComponent() );
			SpawnTrailEffect( World, HitStart, HitInfo.ImpactPoint );
		}
		else
		{
			SpawnTrailEffect( World, HitStart, HitEnd );
		}

		World->GetTimerManager().SetTimer( TimerHandle_ShotTimerExpired, this, &AVpBaseWeapon::ShotTimerExpired, FireRate );

		if( FireSound != nullptr )
		{
			UGameplayStatics::PlaySoundAtLocation( this, FireSound, GetActorLocation() );
		}

		SpawnMuzzleEffect( World, Barrel );
	}
}

void AVpInstantWeapon::SpawnImpactEffect( UWorld* World, const FVector& ImpactLocation, USceneComponent* OtherComp )
{
	if( ImpactEffect != nullptr)
	{
		UParticleSystemComponent* Impact = UGameplayStatics::SpawnEmitterAtLocation( World, ImpactEffect, ImpactLocation );
		FAttachmentTransformRules ImpactRules = FAttachmentTransformRules( EAttachmentRule::KeepRelative, true );
		Impact->AttachToComponent( OtherComp, ImpactRules );
	}
}

void AVpInstantWeapon::SpawnTrailEffect( UWorld* World, const FVector& StartLocation, const FVector& EndLocation )
{
	if( TrailEffect )
	{
		UParticleSystemComponent* Trail = UGameplayStatics::SpawnEmitterAtLocation( World, TrailEffect, StartLocation );
		if( Trail )
		{
			Trail->SetVectorParameter( TrailTargetParam, EndLocation );
		}
	}
}