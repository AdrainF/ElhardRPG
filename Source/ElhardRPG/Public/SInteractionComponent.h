// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELHARDRPG_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void PrimaryInteract();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
