// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionComponent.h"
#include "SAction.h"

USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USActionComponent::AddAction(TSubclassOf<USAction> ActionClass)
{
	// Check if ActionClass is not null
	if (!ensure(ActionClass))
	{
		return;
	}
	//Create new Action object and adding it to the array
	USAction* NewAction = NewObject<USAction>(this, ActionClass);
	if (NewAction)
	{
		Actions.Add(NewAction);
	}
}

bool USActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	// We go through the array checking whether the action we started is available for the pawn
	for (USAction* Action : Actions)
	{
	
		if (Action && Action->ActionName==ActionName)
		{
	//Calling the selected action function
			Action->ActionStart_Implementation(Instigator);
			return true;
		}

		
	}
	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	// We go through the array checking whether the action we started is available for the pawn
	for (USAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			//Calling the selected action function
			Action->ActionStop_Implementation(Instigator);
			return true;
		}


	}
	return false;

}

void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
	// Adding default action specified in Blueprint
	for (TSubclassOf<USAction> ActionClass : DefaultAtions)
	{
		AddAction(ActionClass);
	}

}

void USActionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);

}


