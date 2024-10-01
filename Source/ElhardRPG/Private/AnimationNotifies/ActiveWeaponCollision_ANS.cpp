// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationNotifies/ActiveWeaponCollision_ANS.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "Weapons/Melee/SMeleeWeaponBase.h"

void UActiveWeaponCollision_ANS::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration)
{

	TArray<USceneComponent*> Childrens;
	 MeshComp->GetChildrenComponents(true,Childrens);

	 for (USceneComponent* ChildComp: Childrens)
	 {
		if (ChildComp)
		{

			ASMeleeWeaponBase* Weapon = Cast<ASMeleeWeaponBase>(ChildComp->GetAttachParentActor());
			if (Weapon)
			{
				Weapon->StartWeapoCollison();
			}
		}
		 
	 }

}

void UActiveWeaponCollision_ANS::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{

	TArray<USceneComponent*> Childrens;
	MeshComp->GetChildrenComponents(true, Childrens);

	for (USceneComponent* ChildComp : Childrens)
	{
		if (ChildComp)
		{

			ASMeleeWeaponBase* Weapon = Cast<ASMeleeWeaponBase>(ChildComp->GetAttachParentActor());
			if (Weapon)
			{
				Weapon->StopWeapoCollison();
			}
		}

	}

}
