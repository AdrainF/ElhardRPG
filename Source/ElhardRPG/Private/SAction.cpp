// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "SActionComponent.h"

USAction::USAction()
{

}

void USAction::ActionStart_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Runing: %s"), *GetNameSafe(this));

	// Adding specified in Blueprint Tags
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;

}

void USAction::ActionStop_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);
	// Removing specified in Blueprint Tags
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

FGameplayTagContainer USAction::GetBlocingTags()
{
	return BlockingTags;
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockingTags))
	{
		return false;
	}
	return true;
}

bool USAction::IsRunning()
{
	return bIsRunning;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}
