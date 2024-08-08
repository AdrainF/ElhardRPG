// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SBTTask_ClearFocus.h"
#include "AI/SAI_EnemyBase.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BrainComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "AI/SAI_EnemyController.h"

EBTNodeResult::Type USBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ASAI_EnemyBase* AIPawn = CastChecked<ASAI_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (AIPawn)
	{

		AAIController* AIController = Cast<AAIController>(AIPawn->GetController());
		if (AIController)
		{		
			ASAI_EnemyController* EnemyController = Cast<ASAI_EnemyController>(AIController);
			if (EnemyController)
			{				
				EnemyController->SetIsFocusing(false);
				return EBTNodeResult::Succeeded;
			}
		}
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}
