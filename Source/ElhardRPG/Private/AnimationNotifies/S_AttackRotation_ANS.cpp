// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationNotifies/S_AttackRotation_ANS.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ActorComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"



void US_AttackRotation_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ACharacter* MyCharacter = Cast<ACharacter>(MeshComp->GetOwner());

	if (MyCharacter)
	{
		UCharacterMovementComponent* MovemntComp = Cast<UCharacterMovementComponent>(MyCharacter->GetMovementComponent());

		if (MovemntComp)
		{
			MovemntComp->bAllowPhysicsRotationDuringAnimRootMotion = true;
			
		}

		
	}
	
}

void US_AttackRotation_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacter* MyCharacter = Cast<ACharacter>(MeshComp->GetOwner());

	if (MyCharacter)
	{
		UCharacterMovementComponent* MovemntComp = Cast<UCharacterMovementComponent>(MyCharacter->GetMovementComponent());

		if (MovemntComp)
		{
			MovemntComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
			
		}


	}
	
}
