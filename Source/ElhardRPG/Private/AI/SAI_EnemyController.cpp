// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAI_EnemyController.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/AIController.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Hearing.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Damage.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISenseConfig_Hearing.h"

ASAI_EnemyController::ASAI_EnemyController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ASAI_EnemyController::OnPerceptionUpdatedDelegate);

}

void ASAI_EnemyController::SetEnemyState(EnemyState State)
{
	GetBlackboardComponent()->SetValueAsEnum(EnemyStateKeyName, State);

	

}

AActor* ASAI_EnemyController::GetAttackTarget()
{
	return TargtActor;
}

bool ASAI_EnemyController::GetIsFocusing()
{
	return bIsFocusing;
}

void ASAI_EnemyController::SetIsFocusing(bool Value)
{
	bIsFocusing = Value;
	if (Value)
	{
		SetFocus(TargtActor);
	}
	else
	{
		K2_ClearFocus();
	}
	
}

void ASAI_EnemyController::HandleSightSense(AActor*  SensedActor)
{		
	GetBlackboardComponent()->SetValueAsObject(TargetActorKeyName, SensedActor);
		SetEnemyState(EnemyState::Attacking);
		TargtActor = SensedActor;
}

void ASAI_EnemyController::HandleHearingSense()
{
	SetEnemyState(EnemyState::Investigating);
	GetBlackboardComponent()->SetValueAsVector(InvestigationLocation, AIStimulusLocation);
}

void ASAI_EnemyController::HandleDamageSense(AActor* SensedActor)
{
	GetBlackboardComponent()->SetValueAsObject(TargetActorKeyName, SensedActor);
	SetEnemyState(EnemyState::Attacking);
}

void ASAI_EnemyController::OnPerceptionUpdatedDelegate(const TArray<AActor*>& UpdatedActors)
{
		for (AActor* Actor : UpdatedActors) {

		if (CanSenseActor(Actor, ESenseEnum::Sight))
		{
			
			UE_LOG(LogTemp, Warning, TEXT("SightSense"));
			HandleSightSense(Actor);
		}
		if (CanSenseActor(Actor, ESenseEnum::Hearing)) {
			HandleHearingSense();
			UE_LOG(LogTemp, Warning, TEXT("HearingSense"));
			
		}
		if (CanSenseActor(Actor, ESenseEnum::Damage)) {
			HandleDamageSense(Actor);
			UE_LOG(LogTemp, Warning, TEXT("DamageSense"));
		}
	}
}

bool ASAI_EnemyController::CanSenseActor(AActor* Actor, ESenseEnum Sense)
{
	FActorPerceptionBlueprintInfo  Info;
	TSubclassOf<UAISense> StimuledSense;

	
	bool bPrecepted=PerceptionComp->GetActorsPerception(Actor, Info);
	 if (bPrecepted)
	 {
	
		for(FAIStimulus SenseStimulus : Info.LastSensedStimuli)
		{
			
			StimuledSense =UAIPerceptionSystem::GetSenseClassForStimulus(Actor, SenseStimulus);

			if (StimuledSense)
			{

				UE_LOG(LogTemp, Warning, TEXT("Sense: %s"), *GetNameSafe(StimuledSense));
				//	UE_LOG(LogTemp, Warning, TEXT("Sense: %s"), *GetNameSafe(test));
				switch (Sense)
				{
				case Sight:
					if (StimuledSense == UAISense_Sight::StaticClass())
					{
						
						return true;
					}
					else
					{
						return false;
					}
					break;
				case Hearing:
					if (StimuledSense == UAISense_Hearing::StaticClass())
					{
						AIStimulusLocation = SenseStimulus.StimulusLocation;
						return true;
					}
					else
					{

						return false;
					}
					break;
				case Damage:
					if (StimuledSense == UAISense_Damage::StaticClass())
					{

						return true;
					}
					else
					{
						return false;
					}

					break;
				case None:
					return false;
					break;
				default:
					return false;
					break;
				}
			}
	
		}
		UE_LOG(LogTemp, Warning, TEXT("dupa3"));
	 }
		return false;

}

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
		
		GetBlackboardComponent()->SetValueAsEnum(EnemyStateKeyName, EnemyStateEnum);

	}

}
