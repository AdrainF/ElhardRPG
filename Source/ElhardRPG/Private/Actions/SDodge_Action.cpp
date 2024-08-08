// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SDodge_Action.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "SActionComponent.h"

void USDodge_Action::ActionStart_Implementation(AActor* Instigator)
{
	Super::ActionStart_Implementation(Instigator);

	DodgeImplementation(Instigator);
}

void USDodge_Action::ActionStop_Implementation(AActor* Instigator)
{
	Super::ActionStop_Implementation(Instigator);
}

bool USDodge_Action::GetIsRolling()
{
	return bIsRolling;
}

void USDodge_Action::SetIsRolling(bool Value)
{
	bIsRolling = Value;
}

void USDodge_Action::SaveDodge(AActor* Instigator)
{
	DodgeImplementation(Instigator);
	bIsRolling = false;
}

void USDodge_Action::DodgeImplementation(AActor* Instigator)
{
	ACharacter* InstigatorChar = Cast<ACharacter>(Instigator);

	if (InstigatorChar)
	{
		checkf(DodgeMontage, TEXT("DodgeMontage was not specifed"));
		InstigatorChar->PlayAnimMontage(DodgeMontage);

		float MontageLength = DodgeMontage->GetPlayLength();

		FTimerDelegate ResetDelagate;
		ResetDelagate.BindUFunction(this, "DodgeReset", Instigator);

		GetWorld()->GetTimerManager().SetTimer(TimeToRestet, ResetDelagate, MontageLength, false);

	}

}

void USDodge_Action::DodgeReset(AActor* Instigator)
{
	GetWorld()->GetTimerManager().ClearTimer(TimeToRestet);
	ActionStop_Implementation(Instigator);
}

bool USDodge_Action::CanStart_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockingTags))
	{
		bIsRolling = true;
		return false;
	}
	return true;
}
