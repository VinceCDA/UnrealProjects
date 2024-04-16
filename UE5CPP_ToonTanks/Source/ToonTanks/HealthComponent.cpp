// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	_healthValue = _maxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	_toonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealthComponent::DamageTaken(AActor* damagedActor, float damageAmount, const UDamageType* damageType, AController* instigator, AActor* damageCauser)
{
	if (damageAmount <= 0.0f)
	{
		return;
	}

	_healthValue -= damageAmount;

	if (_toonTanksGameMode && _healthValue <= 0)
	{
		_toonTanksGameMode->ActorDied(damagedActor);
	}

	UE_LOG(LogTemp, Display, TEXT("Healt : %f"), _healthValue);
}

