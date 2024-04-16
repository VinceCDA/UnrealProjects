// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* deadActor);
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool gameWon);
private:
	class ATank* _tank;
	class AToonTanksPlayerController* _playerController;

	float _startDelay = 3.0f;
	int _towerCount = 0;

	int GetNumberOfTower() const;
	void HandleGameStart();
};
