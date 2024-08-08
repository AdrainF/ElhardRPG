// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class ELHARDRPG_API USBTTask_SetFocus : public UBTTaskNode
{
	GENERATED_BODY()

public:

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};