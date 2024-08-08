// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SDodge_Action.generated.h"

/**
 * 
 */
class UAnimMontage;
UCLASS(Blueprintable)
class ELHARDRPG_API USDodge_Action : public USAction
{
	GENERATED_BODY()

public:

	bool GetIsRolling();
	void SetIsRolling(bool Value);
	void SaveDodge(AActor* Instigator);

	virtual void ActionStart_Implementation(AActor* Instigator)  override;
	virtual void ActionStop_Implementation(AActor* Instigator)  override;

	void DodgeImplementation(AActor* Instigator);
	UFUNCTION()
	void DodgeReset(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly,Category="Animation")
		UAnimMontage* DodgeMontage=nullptr;


protected:

	bool bIsRolling = false;

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	FTimerHandle TimeToRestet;
	
	
};
