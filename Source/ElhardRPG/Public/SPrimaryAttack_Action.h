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
	 * Function that start playing combo attack
	 * @param Instigator Actor calling the function
	 */
	virtual void ActionStart_Implementation(AActor* Instigator) override;
	/**
	 *Function that remove tags
	 * @param Instigator Actor calling the function
	 */
	virtual void ActionStop_Implementation(AActor* Instigator) override;
	// Function called over time
	//UFUNCTION()
	//	void AttackDelay_Elapsed(ACharacter* CharacterActor);
	// Function that set default primary attack
	UFUNCTION(BlueprintNativeEvent)
		void SetDefaultAttack();
	// Function that set next animation stage
	UFUNCTION(BlueprintNativeEvent)
		void SetNextAttack(FName AttackName);
	/**
	* Function check if action is already running and set AttackCombo value
	* @param Instigator Actor calling the function
	* Return true if we can call Action
	*/
	virtual bool CanStart_Implementation(AActor* Instigator) override;
	/**
	* Function that play primary attack animation
	* @param Instigator Actor calling the function
	*/
	void PrimaryAttack(AActor* Instigator);
	//Function return bAttackCombo
	bool GetAttackCombo();
	//Function that set bAttackCombo value
	void SetAttackCombo(bool Value);
protected:
	//Store if we are playing combo attack
	bool bAttackCombo = false;
	// Store delay before ending action
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackDelay = 0;
	// Store attack animation
	UPROPERTY(EditDefaultsOnly, Category = "AnimClass")
		UAnimMontage* AnimClass = nullptr;
	UPROPERTY(EditDefaultsOnly,Category="Attack")
		FName DeafultAttackName=TEXT("Primary01");
	UPROPERTY(EditDefaultsOnly,Category="Attack")
		FName PrimaryAttackName = TEXT("Primary01");
};
