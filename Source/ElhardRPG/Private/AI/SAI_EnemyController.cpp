// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAI_EnemyController.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/AIController.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Pawn.h"

void ASAI_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ASAI_EnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr!")))
	{
		RunBehaviorTree(BehaviorTree);

		APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		GetBlackboardComponent()->SetValueAsObject(TargetActorKeyName, MyPawn);
		GetBlackboardComponent()->SetValueAsEnum(EnemyStateKeyName, EnemyStateEnum);

	}
}
