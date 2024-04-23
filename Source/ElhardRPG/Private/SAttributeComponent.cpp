// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}


float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetHealthMax()
{
	return HealthMax;
}

float USAttributeComponent::GetStamina()
{
	return Stamina;
}

float USAttributeComponent::GetGetStaminaMax()
{
	return StaminaMax;
}

bool USAttributeComponent::ApplyOnHealthChange(const float Delta)
{
	float NewHealth = FMath::Clamp(Health + Delta, 0.f, HealthMax);
	Health = NewHealth;
	OnHealthChange.Broadcast(nullptr, this, Health, Delta);
	return true;
}

