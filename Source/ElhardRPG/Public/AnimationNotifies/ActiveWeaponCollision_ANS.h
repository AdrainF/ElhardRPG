// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ActiveWeaponCollision_ANS.generated.h"

/**
 * 
 */
UCLASS()
class ELHARDRPG_API UActiveWeaponCollision_ANS : public UAnimNotifyState
{
	GENERATED_BODY()
	

public:
	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;



	

};
