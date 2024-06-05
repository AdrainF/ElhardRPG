// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SPatrolRoute.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h"

// Sets default values
ASPatrolRoute::ASPatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoutePath=CreateDefaultSubobject<USplineComponent>("RoutePath");
	RoutePath->SetupAttachment(RootComponent);
}

void ASPatrolRoute::IncrementRoutPoint()
{
	CurrentPathIndex += Direction;

	if (CurrentPathIndex==(RoutePath->GetNumberOfSplinePoints()-1))
	{
		Direction = -1;
	}
	else
	{
		if (CurrentPathIndex==0)
		{
			Direction = 1;
		}

	}
}

FVector ASPatrolRoute::GetSlinePointLocation()
{
	FVector RoutPointLocation;
	RoutPointLocation=RoutePath->GetLocationAtSplinePoint(CurrentPathIndex, ESplineCoordinateSpace::World);

	return RoutPointLocation;

}

