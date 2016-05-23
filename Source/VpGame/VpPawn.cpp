// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "VpGame.h"
#include "VpPawn.h"
#include "VpBaseWeapon.h"
#include "TimerManager.h"

const FName AVpPawn::MoveUpBinding("MoveUp");
const FName AVpPawn::MoveRightBinding("MoveRight");

AVpPawn::AVpPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	MoveSpeed = 1000.0f;
}

void AVpPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PrimaryWeapon = GetWorld()->SpawnActor<AVpBaseWeapon>( PrimaryWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator );
	PrimaryWeapon->SetActorLocation( GetActorLocation() + PrimaryWeapon->GetPositionOffset() );
	PrimaryWeapon->GetRootComponent()->AttachTo( RootComponent, NAME_None, EAttachLocation::KeepWorldPosition );
	PrimaryWeapon->Initialize( ShipMeshComponent );
}

void AVpPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAxis(MoveUpBinding);
	InputComponent->BindAxis(MoveRightBinding);

	InputComponent->BindAction( "FirePrimaryWeapon", IE_Pressed, PrimaryWeapon, &AVpBaseWeapon::OnStartFiring );
	InputComponent->BindAction( "FirePrimaryWeapon", IE_Released, PrimaryWeapon, &AVpBaseWeapon::OnStopFiring );
}

void AVpPawn::Tick(float DeltaSeconds)
{
	Move( DeltaSeconds );
}

void AVpPawn::Move( float DeltaSeconds )
{
	// Find movement direction
	const float UpValue = GetInputAxisValue( MoveUpBinding );
	const float RightValue = GetInputAxisValue( MoveRightBinding );

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector( 0.f, RightValue, UpValue ).GetClampedToMaxSize( 1.0f );

	const FVector RotateDirection = FVector( 1.0f, RightValue, UpValue ).GetClampedToMaxSize( 1.0f );

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	const FRotator TargetRotation = MoveDirection.Rotation();// Movement.Rotation();
	FRotator NewRotation = FMath::Lerp( GetActorRotation(), TargetRotation, 0.05f );
	NewRotation.Pitch = FMath::ClampAngle(NewRotation.Pitch, -30.0f, 30.0f);
	NewRotation.Yaw = FMath::ClampAngle(NewRotation.Yaw, -30.0f, 30.0f);

	// If non-zero size, move this actor
	//if( Movement.SizeSquared() > 0.0f )
	//{
		
		FHitResult Hit( 1.f );
		bool Move = RootComponent->MoveComponent( Movement, NewRotation, true, &Hit );

		if( Hit.IsValidBlockingHit() )
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject( Movement, Normal2D ) * (1.f - Hit.Time);
			RootComponent->MoveComponent( Deflection, NewRotation, true );
		}
	//}

	
}