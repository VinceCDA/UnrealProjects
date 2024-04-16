// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = _capsuleComponent;

	_baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	_baseMesh->SetupAttachment(_capsuleComponent);

	_turrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	_turrentMesh->SetupAttachment(_baseMesh);

	_projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	_projectileSpawnPoint->SetupAttachment(_turrentMesh);
}

void ABasePawn::HandleDestruction()
{
	if (_deathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, _deathParticles, GetActorLocation(), GetActorRotation());
	}
	if (_deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, _deathSound, GetActorLocation());
	}
	if (_deathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(_deathCameraShakeClass);
	}
}

void ABasePawn::RotateTurrent(FVector lookAtTarget, float deltatime)
{
	FVector toTarget = lookAtTarget - _turrentMesh->GetComponentLocation();
	FRotator lookAtRotation = toTarget.Rotation();
	lookAtRotation.Roll = 0;
	lookAtRotation.Pitch = 0;
	_turrentMesh->SetWorldRotation(FMath::RInterpTo(_turrentMesh->GetComponentRotation(), lookAtRotation, deltatime, 5.0f));
}

void ABasePawn::Fire()
{
	DrawDebugSphere(GetWorld(), _projectileSpawnPoint->GetComponentLocation(), 10.0f, 10, FColor::Blue, false, 3.0f);
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>
		(
			_projectileClass,
			_projectileSpawnPoint->GetComponentLocation(),
			_projectileSpawnPoint->GetComponentRotation()
		);
	projectile->SetOwner(this);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



