// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <../../../../../../../Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h>
#include "SActionComponent.generated.h"

class USAction;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ELHARDRPG_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USActionComponent();

protected:
	// Array that stores the actions available to the pawn
	UPROPERTY()
		TArray<USAction*> Actions;
	// Array that stores the default pawn actions
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		TArray<TSubclassOf<USAction>> DefaultAtions;

public:
	// Container that stores Blocking and Granting Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FGameplayTagContainer ActiveGameplayTags;
	// Function that adds actions to the array
	UFUNCTION(BlueprintCallable, Category = "Action")
		void AddAction(TSubclassOf<USAction> ActionClass);
	/**
	 * Function that start executing available actions
	 * @param Instigator Actor calling the function
	 * @param ActionName Name of calling function
	 */
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StartActionByName(AActor* Instigator, FName ActionName);
	/**
	 * Function called after action end
	 * @param Instigator Actor calling functions
	 * @param ActionName Name of calling function
	 */
	UFUNCTION(BlueprintCallable, Category = "Action")
		bool StopActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Action")
		USAction* GetActionByName(FName ActionName);

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
