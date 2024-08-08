// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SBTTask_SetStateAsPassive.h"
#include "AI/SAI_EnemyBase.h"
#include "AIController.h"
#include "AI/SAI_EnemyController.h"

EBTNodeResult::Type USBTTask_SetStateAsPassive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASAI_EnemyBase* AIPawn = CastChecked<ASAI_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (AIPawn)
	{
		ASAI_EnemyController* AIContoller = Cast<ASAI_EnemyController>(AIPawn->GetController());
		if (AIContoller)
		{
			AIContoller->SetEnemyState(EnemyState::Passive);
			return EBTNodeResult::Succeeded;
		}	
	}
	return EBTNodeResult::Failed;	
}
