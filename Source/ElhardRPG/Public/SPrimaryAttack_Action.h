// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SPrimaryAttack_Action.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class ELHARDRPG_API USPrimaryAttack_Action : public USAction
{
	GENERATED_BODY()

public:
	/**
	 *Function that play primary attack animation
	 * @param Instigator Actor calling the function
	 */
	virtual void ActionStart_Implementation(AActor* Instigator) override;
	/**
	 *Function that remove tags
	 * @param Instigator Actor calling the function
	 */
	virtual void ActionStop_Implementation(AActor* Instigator) override;
	// Function called over time
	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* CharacterActor);


protected:
	// Store delay before ending action
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackDelay = 0;
	// Store attack animation
	UPROPERTY(EditDefaultsOnly, Category = "AnimClass")
		UAnimMontage* AnimClass = nullptr;

};
