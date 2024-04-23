// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttack_Action.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Animation/AnimNotifies/AnimNotifyState.h>
#include "SActionComponent.h"

void USPrimaryAttack_Action::ActionStart_Implementation(AActor* Instigator)
{
	Super::ActionStart_Implementation(Instigator);
	
		PrimaryAttack(Instigator);	
}

void USPrimaryAttack_Action::ActionStop_Implementation(AActor* Instigator)
{
	Super::ActionStop_Implementation(Instigator);

}

void USPrimaryAttack_Action::AttackDelay_Elapsed(ACharacter* CharacterActor)
{
//	ActionStop_Implementation(CharacterActor);
}

void USPrimaryAttack_Action::SetDefaultAttack_Implementation()
{
	PrimaryAttackName = DeafultAttackName;
}

void USPrimaryAttack_Action::SetNextAttack_Implementation(FName AttackName)
{
	PrimaryAttackName = AttackName;
}

void USPrimaryAttack_Action::PrimaryAttack(AActor* Instigator)
{	
	// Casting Instigator to ACharacter
	ACharacter* MyCharacter = Cast<ACharacter>(Instigator);
	// Check if actor that call the function was ACharacter type
	if (MyCharacter )
	{
		// Check if AnimClass was specified
		if (ensure(AnimClass))
		{
			// Start attack animation
			MyCharacter->PlayAnimMontage(AnimClass, 1.f, PrimaryAttackName);

			FString FailedMsg = FString::Printf(TEXT("%s"), *PrimaryAttackName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FailedMsg);
			FTimerHandle TimeHandler_AttackDelay;
			FTimerDelegate Delegate;
			// Create delegate to AttackDelay_Elaped function that passing Character object
			Delegate.BindUFunction(this, "AttackDelay_Elapsed", MyCharacter);
			//Call function in delay
			GetWorld()->GetTimerManager().SetTimer(TimeHandler_AttackDelay, Delegate, AttackDelay, false);
		}
	}
}

bool USPrimaryAttack_Action::GetAttackCombo()
{
	return bAttackCombo;
}

void USPrimaryAttack_Action::SetAttackCombo(bool Value)
{
	bAttackCombo = Value;
}

bool USPrimaryAttack_Action::CanStart_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockingTags))
	{
		SetAttackCombo(true);
		return false;
	}
	return true;
}
