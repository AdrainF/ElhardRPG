// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include <SPlayerCharacter.h>
#include <SGameplayInterface.h>

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void USInteractionComponent::PrimaryInteract()
{
	TArray<struct FHitResult> OutHits;
	FVector Start;
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionShape CollisionShape;
	float Radius = 30.0f;
	CollisionShape.SetSphere(Radius);
	FCollisionQueryParams Params;
	ASPlayerCharacter* MyCharacter = Cast<ASPlayerCharacter>(GetOwner());
	Start = MyCharacter->GetPawnViewLocation();
	End = MyCharacter->GetPawnViewLocation() + (MyCharacter->GetControlRotation().Vector() * 5000);
	Params.AddIgnoredActor(MyCharacter);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape, Params);

	FColor LineColor = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->Implements<USGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyCharacter);
			ISGameplayInterface::Execute_Interact(HitActor, MyPawn);

			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
			break;
		}

	}
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);

}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

