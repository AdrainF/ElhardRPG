// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAI_EnemyController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum  EnemyState :uint8
{	
    Passive			UMETA(DisplayName = "Passive"),
	Stuned			UMETA(DisplayName = "Stuned"),
    Investigating	UMETA(DisplayName = "Investigating"),
	Attacking		UMETA(DisplayName = "Attacking"),
    Dead			UMETA(DisplayName = "Dead")
};

UCLASS()
class ELHARDRPG_API ASAI_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetActorKeyName;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName EnemyStateKeyName;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TEnumAsByte<EnemyState> EnemyStateEnum;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
