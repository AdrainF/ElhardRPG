// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_SetMovementMode.generated.h"

/**
 *
 */
UCLASS()
class ELHARDRPG_API USBTTask_SetMovementMode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	USBTTask_SetMovementMode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
		TEnumAsByte<EMovementEnum> MovementEnum;
	
};
