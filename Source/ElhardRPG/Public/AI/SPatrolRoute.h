// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPatrolRoute.generated.h"

class USplineComponent;
UCLASS()
class ELHARDRPG_API ASPatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPatrolRoute();

protected:
	UPROPERTY(EditDefaultsOnly)
	USplineComponent* RoutePath;

	int CurrentPathIndex = 0;
	int Direction = 1;
public:
	UFUNCTION()
	void IncrementRoutPoint();

	UFUNCTION()
	FVector GetSlinePointLocation();
};
