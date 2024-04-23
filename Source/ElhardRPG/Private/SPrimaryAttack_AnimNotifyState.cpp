// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttack_AnimNotifyState.h"
#include "SPlayerCharacter.h"
#include "SPrimaryAttack_Action.h"
#include "SActionComponent.h"


void USPrimaryAttack_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

	ASPlayerCharacter* MyActor = Cast<ASPlayerCharacter>(MeshComp->GetOwner());

	if (MyActor)
	{
		USActionComponent* ActionComp = MyActor->GetComponentByClass<USActionComponent>();

		if (ActionComp)
		{
			USPrimaryAttack_Action* MyAction = Cast<USPrimaryAttack_Action>(ActionComp->GetActionByName("PrimaryAttack"));
			if (MyAction)
			{
				MyAction->SetNextAttack(PrimaryNextAttack);
				//return true;
			}
		}
	}
}

void USPrimaryAttack_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ASPlayerCharacter* MyActor = Cast<ASPlayerCharacter>(MeshComp->GetOwner());

	if (MyActor)
	{
		USActionComponent* ActionComp = MyActor->GetComponentByClass<USActionComponent>();

		if (ActionComp)
		{
			USPrimaryAttack_Action* MyAction = Cast<USPrimaryAttack_Action>(ActionComp->GetActionByName("PrimaryAttack"));
			if (MyAction)
			{
				if (MyAction->GetAttackCombo())
				{
					MyAction->PrimaryAttack(MyActor);
					MyAction->SetAttackCombo(false);
					
				}
				else
				{
					MyAction->ActionStop_Implementation(MyActor);
					MyAction->SetDefaultAttack();					
				}										
			}
		}
	}	
}
