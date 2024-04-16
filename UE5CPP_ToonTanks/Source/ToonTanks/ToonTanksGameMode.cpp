// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include"Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if (deadActor == _tank)
	{
		_tank->HandleDestruction();
		if (_playerController)
		{
			_playerController->SetPlayerControllerEnabled(false);
		}
		GameOver(false);
	}
	else if(ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->HandleDestruction();

		_towerCount--;

		if (_towerCount == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();

}

int AToonTanksGameMode::GetNumberOfTower() const
{
	TArray<AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), towers);
	return towers.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	_towerCount = GetNumberOfTower();
	_tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	_playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (_playerController)
	{
		_playerController->SetPlayerControllerEnabled(false);

		FTimerHandle playerEnableTimerHandle;
		FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(_playerController, &AToonTanksPlayerController::SetPlayerControllerEnabled, true);
		GetWorldTimerManager().SetTimer(playerEnableTimerHandle, timerDelegate, _startDelay, false);
	}
}
