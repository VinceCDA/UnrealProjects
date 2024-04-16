// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float _speed = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float _turnSpeed = 100.0f;
	bool _isAlive = true;
	APlayerController* _playerController;

	void Move(float value);
	void Turn(float value);
	void MoveToFloor();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetPlayerController() const { return _playerController; };
	void HandleDestruction();
	bool IsAlive() const { return _isAlive; };
};
