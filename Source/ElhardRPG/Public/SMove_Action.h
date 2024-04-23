// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SMove_Action.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ELHARDRPG_API USMove_Action : public USAction
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
};
