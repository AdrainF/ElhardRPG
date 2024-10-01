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
UENUM(BlueprintType)
enum  ESenseEnum :uint8
{
    Sight	UMETA(DisplayName = "Sight"),
    Hearing	UMETA(DisplayName = "Hearing"),
    Damage		UMETA(DisplayName = "Damage"),
    None	UMETA(DisplayName = "None")
};

UCLASS()
class ELHARDRPG_API ASAI_EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASAI_EnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable)
	AActor* GetAttackTarget();
	UFUNCTION(BlueprintCallable)
	bool GetIsFocusing();

	UFUNCTION(BlueprintCallable)
	void SetIsFocusing(bool Value);
	UFUNCTION(BlueprintCallable)
	void SetEnemyState(EnemyState State);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName TargetActorKeyName;
	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName EnemyStateKeyName;
	UPROPERTY(EditAnywhere, Category="AI")
	TEnumAsByte<EnemyState> EnemyStateEnum;
	UPROPERTY(EditAnywhere, Category="AI")
		FName InvestigationLocation;

	UPROPERTY(EditAnywhere,Category="Component")
		UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(EditAnywhere,Category="AI")
		AActor* TargtActor;

	FVector AIStimulusLocation;

	bool bIsFocusing=false;
	
	void HandleSightSense(AActor* SensedActor);
	void HandleHearingSense();
	void HandleDamageSense(AActor* SensedActor);	
	UFUNCTION()
	virtual void OnPerceptionUpdatedDelegate(const TArray<AActor*>& UpdatedActors) ;
	UFUNCTION(BlueprintCallable)
	bool CanSenseActor(AActor* Actor,ESenseEnum Sense);

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
