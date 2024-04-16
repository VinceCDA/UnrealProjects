// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_springArm->SetupAttachment(RootComponent);
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_springArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	_playerController = Cast<APlayerController>(GetController());

	MoveToFloor();

}

void ATank::Move(float value)
{
	//UE_LOG(LogTemp, Display, TEXT("Move : %f"), value);
	FVector deltaLocation = FVector::Zero();
	deltaLocation.X = value * UGameplayStatics::GetWorldDeltaSeconds(this) * _speed;
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * _turnSpeed;
	AddActorLocalRotation(deltaRotation, true);
}

void ATank::MoveToFloor()
{

	FHitResult hitResult;
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(this);
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation + FVector::ZAxisVector * 1000.0f;

	GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility, collisionParameters);

	SetActorLocation(hitResult.ImpactPoint, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_playerController)
	{
		FHitResult hitResult;
		_playerController->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		RotateTurrent(hitResult.ImpactPoint, DeltaTime);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10.0f, 10, FColor::Red);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	_isAlive = false;
}
