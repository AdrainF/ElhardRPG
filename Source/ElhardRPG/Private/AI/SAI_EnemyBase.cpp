// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAI_EnemyBase.h"
#include "AI/SPatrolRoute.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Hearing.h"
#include "../../../../../../../Source/Runtime/AIModule/Classes/Perception/AISense_Damage.h"
#include "AI/SAI_EnemyController.h"

// Sets default values
ASAI_EnemyBase::ASAI_EnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ASAI_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASAI_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASAI_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASAI_EnemyBase::MeleeAttack()
{
	checkf(AttackAnim, TEXT("AttacAnim was not specified!!!"))
	PlayAnimMontage(AttackAnim);
}

void ASAI_EnemyBase::SetMovementMode(EMovementEnum MovementMode)
{

	AIMovement = MovementMode;

	switch (MovementMode)
	{
	case Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		break;
	case Walk:
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
		break;
	case Run:
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		break;
	case Sprint:
		GetCharacterMovement()->MaxWalkSpeed = 550.0f;
		break;
	default:
		break;
	}

}

EMovementEnum ASAI_EnemyBase::GetMovementMode()
{
	return AIMovement;
}
