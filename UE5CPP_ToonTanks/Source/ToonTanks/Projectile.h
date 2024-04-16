// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _staticMesh;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* _movementComponent;
	UPROPERTY(EditAnywhere)
	float _damage = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* _hitParticles;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* _particlesComponent;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* _launchSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* _hitSound;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> _hitCameraShakeClass;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hitResult);
};
