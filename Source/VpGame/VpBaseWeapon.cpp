#include "VpGame.h"
#include "VpBaseWeapon.h"
#include "VpProjectile.h"
#include "VpPawn.h"

AVpBaseWeapon::AVpBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshAsset( TEXT( "/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile" ) );

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "WeaponMesh0" ) );
	WeaponMesh->SetStaticMesh( WeaponMeshAsset.Object );
	WeaponMesh->AttachToComponent( RootComponent, FAttachmentTransformRules::KeepRelativeTransform );
	WeaponMesh->BodyInstance.SetCollisionProfileName( "Weapon" );
	RootComponent = WeaponMesh;

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio( TEXT( "/Game/TwinStick/Audio/TwinStickFire.TwinStickFire" ) );
	FireSound = FireAudio.Object;

	FireRate = 0.1f;
	bCanFire = true;
}

void AVpBaseWeapon::Initialize(UStaticMeshComponent* ShipMesh, AVpPawn* MyPawnIn)
{
	MyPawn = MyPawnIn;
	UWorld* World = GetWorld();

	if( World )
	{
		for( auto SocketName : BarrelSocketNames )
		{
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
	const FVector FireDirection = MyPawn->GetAimDirection();

	if( bCanFire == true )
	{
		if( bIsFiring == true )
		{
			if( FireDirection.Size() > 0.f )
			{
				Fire( FireDirection );

				bCanFire = false;
			}
		}
	}
}

void AVpBaseWeapon::Fire( const FVector& FireDirection )
{

}

const AActor* const AVpBaseWeapon::GetNextBarrel()
{
	AActor* Barrel = Barrels[BarrelIndex];

	++BarrelIndex;
	if( BarrelIndex >= Barrels.Num() ) BarrelIndex = 0;

	return Barrel;
}

void AVpBaseWeapon::SpawnMuzzleEffect( UWorld* World, const AActor* const Barrel )
{
	if( MuzzleEffect != nullptr )
	{
		UParticleSystemComponent* MuzzleFlash = UGameplayStatics::SpawnEmitterAtLocation( World, MuzzleEffect, Barrel->GetActorLocation() );
		FAttachmentTransformRules MuzzleRules = FAttachmentTransformRules( EAttachmentRule::KeepRelative, true );
		MuzzleFlash->AttachToComponent( Barrel->GetRootComponent(), MuzzleRules );
	}
}

void AVpBaseWeapon::ShotTimerExpired()
{
	bCanFire = true;
}