// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChange, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELHARDRPG_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USAttributeComponent();

protected:
	// Attributes
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float HealthMax=100.0f;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float Health=HealthMax;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float StaminaMax=100.0f;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float Stamina= StaminaMax;
	
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable)
		FOnHealthChange OnHealthChange;
	//Getter functions
	UFUNCTION(BlueprintCallable)
	float GetHealth();
	UFUNCTION(BlueprintCallable)
	float GetHealthMax();
	UFUNCTION(BlueprintCallable)
	float GetStamina();
	UFUNCTION(BlueprintCallable)
	float GetGetStaminaMax();
	/**
	 * Function that change Character Health
	 * @param Delta value of Health change
	 */
	UFUNCTION(BlueprintCallable)
	 bool ApplyOnHealthChange(const float Delta);
	
};
