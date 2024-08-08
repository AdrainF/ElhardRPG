// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SPrimaryAttack_AnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ELHARDRPG_API USPrimaryAttack_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

UPROPERTY(EditAnywhere)
		FName PrimaryNextAttack = TEXT("Primary01");


	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
protected:
	
};
