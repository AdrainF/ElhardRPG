// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationNotifies/SDodgEnd_AN.h"
#include "SPlayerCharacter.h"
#include "Actions/SDodge_Action.h"
#include "SActionComponent.h"

void USDodgEnd_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ASPlayerCharacter* MyActor = Cast<ASPlayerCharacter>(MeshComp->GetOwner());

	if (MyActor)
	{
		USActionComponent* ActionComp = MyActor->GetComponentByClass<USActionComponent>();

		if (ActionComp)
		{
			USDodge_Action* MyAction = Cast<USDodge_Action>(ActionComp->GetActionByName("Dodge"));
			if (MyAction)
			{
				if (!MyAction->GetIsRolling())
				{
					MyAction->DodgeReset(MyActor);
				}
			}
		}
	}

}
