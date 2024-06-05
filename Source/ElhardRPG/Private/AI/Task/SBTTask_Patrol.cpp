// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SBTTask_Patrol.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Controller.h"
#include "AIController.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h"
#include "AI/SAI_EnemyBase.h"
#include "AI/SPatrolRoute.h"


EBTNodeResult::Type USBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASAI_EnemyBase* AIPawn = CastChecked<ASAI_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (AIPawn)
	{
		ASPatrolRoute* PassiveRoute = Cast<ASPatrolRoute>(AIPawn->PatrolRoute);
		if (PassiveRoute)
		{
			AAIController* AIControllrt = Cast<AAIController>(AIPawn->GetController());
			if (AIControllrt)
			{
				//UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIPawn->GetController(), PassiveRoute->GetSlinePointLocation());
				EPathFollowingRequestResult::Type MoveResult = AIControllrt->MoveToLocation(PassiveRoute->GetSlinePointLocation(), 50);

				if (MoveResult == 1)
				{
					PassiveRoute->IncrementRoutPoint();
					return EBTNodeResult::Succeeded;
				}
				else
				{
					return EBTNodeResult::Failed;
				}
			}
			return EBTNodeResult::Failed;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;

}
