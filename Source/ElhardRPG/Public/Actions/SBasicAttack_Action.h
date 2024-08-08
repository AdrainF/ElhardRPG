// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SBasicAttack_Action.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ELHARDRPG_API USBasicAttack_Action : public USAction
{
	GENERATED_BODY()
	
public:
	virtual void ActionStart_Implementation(AActor* Instigator) override;
	virtual void ActionStop_Implementation(AActor* Instigator) override;

	UFUNCTION(BlueprintCallable)
	bool GetIsSaveAttack();
	UFUNCTION()
	void SetIsSavedAttack(bool Value);
	UFUNCTION()
	void SaveBasicAttack(AActor* Instigator);
	UFUNCTION()
	void ResetBasicAttack(AActor* Instigator);
protected:
	UPROPERTY(EditDefaultsOnly,Category= "Animation")
	TArray<UAnimMontage*> AttacksArray;

	UFUNCTION()
	void BasicAttack(int Index, AActor* Instigator);

	
	virtual bool CanStart_Implementation(AActor* Instigator) override;

	int AttackIndex = 0;
	bool bIsSaveAttack = false;
	FTimerHandle TimeToRestet;
};
