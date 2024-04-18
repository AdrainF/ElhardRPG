// Fill out your copyright notice in the Description page of Project Settings.


#include "SPrimaryAttack_Action.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h>

void USPrimaryAttack_Action::ActionStart_Implementation(AActor* Instigator)
{
	Super::ActionStart_Implementation(Instigator);

	// Casting Instigator to ACharacter
	ACharacter* MyCharacter = Cast<ACharacter>(Instigator);
	// Check if actor that call the function was ACharacter type
	if (MyCharacter)
	{
		// Check if AnimClass was specified
		if (ensure(AnimClass))
		{
			// Start attack animation
			MyCharacter->PlayAnimMontage(AnimClass);
			
			FTimerHandle TimeHandler_AttackDelay;
			FTimerDelegate Delegate;
			// Create delegate to AttackDelay_Elaped function that passing Character object
			Delegate.BindUFunction(this, "AttackDelay_Elapsed", MyCharacter);
			//Call function in delay
			GetWorld()->GetTimerManager().SetTimer(TimeHandler_AttackDelay, Delegate, AttackDelay, false);
		}

	}

}

void USPrimaryAttack_Action::ActionStop_Implementation(AActor* Instigator)
{
	Super::ActionStop_Implementation(Instigator);

}

void USPrimaryAttack_Action::AttackDelay_Elapsed(ACharacter* CharacterActor)
{
	ActionStop_Implementation(CharacterActor);
}
