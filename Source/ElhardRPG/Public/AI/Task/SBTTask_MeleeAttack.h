// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ELHARDRPG_API USBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USBTTask_MeleeAttack();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	
};
