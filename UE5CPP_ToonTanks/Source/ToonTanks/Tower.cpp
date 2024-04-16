// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include"Tank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	_tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(_fireRateTimerHandle, this, &ATower::CheckFireCondition, _fireRate, true);
	
}
// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurrent(_tank->GetActorLocation(), DeltaTime);
	}

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

bool ATower::InFireRange()
{
	if (_tank)
	{
		float distance = FVector::Dist(GetActorLocation(), _tank->GetActorLocation());

		if (distance < _fireRange)
		{
			return true;
		}
	}

	return false;
}

void ATower::CheckFireCondition()
{
	if (_tank == nullptr)
	{
		return;
	}
	if (InFireRange() && _tank->IsAlive())
	{
		Fire();
	}
}
