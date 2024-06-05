// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/SBTTask_MeleeAttack.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Controller.h"
#include "AIController.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AI/SAI_EnemyBase.h"

USBTTask_MeleeAttack::USBTTask_MeleeAttack()
{
	TargetActorKey.SelectedKeyName = "TargetActor";
}

EBTNodeResult::Type USBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASAI_EnemyBase* AIPawn = CastChecked<ASAI_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()
		->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}

		AIPawn->MeleeAttack();
	return EBTNodeResult::Succeeded;

}
