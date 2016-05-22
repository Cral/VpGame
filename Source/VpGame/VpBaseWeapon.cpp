#include "VpGame.h"
#include "VpBaseWeapon.h"
#include "VpProjectile.h"

AVpBaseWeapon::AVpBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshAsset( TEXT( "/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile" ) );

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "WeaponMesh0" ) );
	WeaponMesh->SetStaticMesh( WeaponMeshAsset.Object );
	WeaponMesh->AttachTo( RootComponent );
	WeaponMesh->BodyInstance.SetCollisionProfileName( "Weapon" );
	RootComponent = WeaponMesh;

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio( TEXT( "/Game/TwinStick/Audio/TwinStickFire.TwinStickFire" ) );
	FireSound = FireAudio.Object;

	FireRate = 0.1f;
	bCanFire = true;
}

void AVpBaseWeapon::Initialize(UStaticMeshComponent* ShipMesh)
{
	UWorld* World = GetWorld();

	if( World )
	{
		for( auto SocketName : BarrelSocketNames )
		{
			//UStaticMeshSocket const * BarrelSocket = ShipMesh->GetSocketByName( SocketName );
			//AActor* Barrel = World->SpawnActor<AActor>();
			AActor* Barrel = World->SpawnActor<AActor>( BarrelClass );
			Barrel->AttachRootComponentTo( ShipMesh, SocketName, EAttachLocation::SnapToTarget );
			Barrels.Add( Barrel );
		}
	}
}

void AVpBaseWeapon::Tick( float DeltaSeconds )
{
	TryFiring();
}

void AVpBaseWeapon::OnStartFiring()
{
	bIsFiring = true;
}

void AVpBaseWeapon::OnStopFiring()
{
	bIsFiring = false;
}

void AVpBaseWeapon::TryFiring()
{
	const FVector FireDirection = FVector( 1.0f, 0.0f, 0.0f );

	if( bCanFire == true && bIsFiring == true )
	{
		UWorld* const World = GetWorld();
		if( World )
		{
			if( Barrels.Num() > 0 )
			{

				AActor* Barrel = Barrels[BarrelIndex];
				AVpProjectile* Projectile = World->SpawnActor<AVpProjectile>( ProjectileClass, Barrel->GetActorLocation(), Barrel->GetActorRotation() );

				World->GetTimerManager().SetTimer( TimerHandle_ShotTimerExpired, this, &AVpBaseWeapon::ShotTimerExpired, FireRate );

				if( FireSound != nullptr )
				{
					UGameplayStatics::PlaySoundAtLocation( this, FireSound, GetActorLocation() );
				}

				++BarrelIndex;
				if( BarrelIndex >= Barrels.Num() ) BarrelIndex = 0;
			}
			else
			{
				//Log no barrels error.
			}
		}

		bCanFire = false;
	}
}

void AVpBaseWeapon::ShotTimerExpired()
{
	bCanFire = true;
}