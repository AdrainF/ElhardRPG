// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SBasicAttack_Action.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "SActionComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Public/TimerManager.h"

void USBasicAttack_Action::ActionStart_Implementation(AActor* Instigator)
{
	Super::ActionStart_Implementation(Instigator);
	BasicAttack(AttackIndex, Instigator);
}

void USBasicAttack_Action::ActionStop_Implementation(AActor* Instigator)
{
	Super::ActionStop_Implementation(Instigator);

}

bool USBasicAttack_Action::GetIsSaveAttack()
{
	return bIsSaveAttack;
}

void USBasicAttack_Action::SetIsSavedAttack(bool Value)
{
	bIsSaveAttack = Value;
}

void USBasicAttack_Action::BasicAttack(int Index, AActor* Instigator)
{
	ACharacter* MyCharacter = Cast<ACharacter>(Instigator);

	if (MyCharacter)
	{
		UAnimMontage* Montage = AttacksArray[Index];
		MyCharacter->PlayAnimMontage(Montage);
		
		float MontageLength = Montage->GetPlayLength();

		FTimerDelegate ResetDelagate;
		ResetDelagate.BindUFunction(this, "ResetBasicAttack", Instigator);
		
		GetWorld()->GetTimerManager().SetTimer(TimeToRestet, ResetDelagate, MontageLength, false);
		
		AttackIndex += 1;

		if (AttackIndex >= AttacksArray.Num())
		{
			AttackIndex = 0;
		}
	}
}

void USBasicAttack_Action::ResetBasicAttack(AActor* Instigator)
{
	GetWorld()->GetTimerManager().ClearTimer(TimeToRestet);
	AttackIndex = 0;
	bIsSaveAttack = false;
	ActionStop_Implementation(Instigator);
}

bool USBasicAttack_Action::CanStart_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockingTags))
	{
		bIsSaveAttack = true;
		return false;
	}
	return true;
}

void USBasicAttack_Action::SaveBasicAttack(AActor* Instigator)
{
	BasicAttack(AttackIndex, Instigator);
	bIsSaveAttack = false;
}
