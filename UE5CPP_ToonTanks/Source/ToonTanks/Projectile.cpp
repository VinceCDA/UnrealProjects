// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = _staticMesh;

	_movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	_movementComponent->InitialSpeed = 1300.0f;
	_movementComponent->MaxSpeed = 1300.0f;

	_particlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trails"));
	_particlesComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	_staticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (_launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, _launchSound, GetActorLocation());
	}
	
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	_staticMesh->OnComponentHit.RemoveDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hitResult)
{
	UE_LOG(LogTemp, Display, TEXT("HIT ! HitComponent : %s, OtherActor : %s, OtherComponent : %s"), *hitComponent->GetName(), *otherActor->GetName(), *otherComponent->GetName());
	AActor* myOwner = GetOwner();
	if (myOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != myOwner)
	{
		UGameplayStatics::ApplyDamage(otherActor, _damage, myOwnerInstigator, this, damageTypeClass);

		if (_hitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, _hitParticles, GetActorLocation(), GetActorRotation());
		}
		if (_hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, _hitSound, GetActorLocation());
		}
		if (_hitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(_hitCameraShakeClass);
		}
		
	}
	

	Destroy();
}

