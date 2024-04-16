// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
private:
	class ATank* _tank;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float _fireRange = 500.0f;
	FTimerHandle _fireRateTimerHandle;
	float _fireRate = 2.0f;
	bool InFireRange();
	void CheckFireCondition();
};
