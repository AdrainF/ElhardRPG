// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <../../../../../../../Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h>
#include "SAction.generated.h"

/**
 *
 */
class USActionComponent;
UCLASS()
class ELHARDRPG_API USAction : public UObject
{
	GENERATED_BODY()

public:
	USAction();
	// Stores name of action
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		FName ActionName;
	/**
	 *Action template function
	 * @param Instigator Actor calling the function
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void ActionStart(AActor* Instigator);
	/**
	 *Action template function
	 * @param Instigator Actor calling the function
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void ActionStop(AActor* Instigator);
	/*
	*/
	FGameplayTagContainer GetBlocingTags();
	UFUNCTION(BlueprintNativeEvent)
	 bool CanStart(AActor* Instigator);
	/**
	 * Return bIsRunning value
	 */
	UFUNCTION(BlueprintCallable)
		bool IsRunning();

	
protected:
	UPROPERTY(EditAnywhere, Category = "Tags")
		FGameplayTagContainer GrantsTags;
	UPROPERTY(EditAnywhere, Category = "Tags")
		FGameplayTagContainer BlockingTags;
	
	 bool bIsRunning = false;
	// Return object that USActonComponent resides in
	UFUNCTION(BlueprintCallable, Category = "Action")
		USActionComponent* GetOwningComponent() const;
};
