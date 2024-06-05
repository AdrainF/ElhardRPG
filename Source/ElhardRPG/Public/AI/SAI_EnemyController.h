// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAI_EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class ELHARDRPG_API ASAI_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
