// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAI_EnemyBase.generated.h"

UENUM(BlueprintType)
enum  EMovementEnum :uint8
{
    Idle	UMETA(DisplayName = "Idle"),
    Walk	UMETA(DisplayName = "Walk"),
    Run		UMETA(DisplayName = "Run"),
    Sprint	UMETA(DisplayName = "Sprint")
};



class ASPatrolRoute;
UCLASS()
class ELHARDRPG_API ASAI_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAI_EnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MeleeAttack();
	UPROPERTY(EditDefaultsOnly, Category = "AttackAnim")
		UAnimMontage* AttackAnim = nullptr;
	UPROPERTY(EditAnywhere, Category="AI")
		ASPatrolRoute* PatrolRoute;

	UFUNCTION(BlueprintCallable)
	void SetMovementMode(EMovementEnum MovementMode);
};
