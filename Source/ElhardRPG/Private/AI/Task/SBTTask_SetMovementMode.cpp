// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SBTTask_SetMovementMode.h"
#include "AI/SAI_EnemyBase.h"
#include "AIController.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

USBTTask_SetMovementMode::USBTTask_SetMovementMode()
{

}

EBTNodeResult::Type USBTTask_SetMovementMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ASAI_EnemyBase* AIPawn = CastChecked<ASAI_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (AIPawn)
	{
		EMovementEnum MovementMode = static_cast<EMovementEnum>(MovementEnum.GetValue());
		AIPawn->SetMovementMode(MovementMode);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

}
