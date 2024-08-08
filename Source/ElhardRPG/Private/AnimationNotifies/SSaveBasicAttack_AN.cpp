// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationNotifies/SSaveBasicAttack_AN.h"
#include "SPlayerCharacter.h"
#include "Actions/SBasicAttack_Action.h"
#include "SActionComponent.h"

void USSaveBasicAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	ASPlayerCharacter* MyActor = Cast<ASPlayerCharacter>(MeshComp->GetOwner());

	if (MyActor)
	{
		USActionComponent* ActionComp = MyActor->GetComponentByClass<USActionComponent>();

		if (ActionComp)
		{
			USBasicAttack_Action* MyAction = Cast<USBasicAttack_Action>(ActionComp->GetActionByName("BasicAttack"));
			if (MyAction)
			{
				if (MyAction->GetIsSaveAttack())
				{
					MyAction->SaveBasicAttack(MyActor);
					MyAction->SetIsSavedAttack(false);
					
				}
			
			}
		
		}
		
	}

}

