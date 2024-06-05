// Fill out your copyright notice in the Description page of Project Settings.


#include "SFocusOnTarget_Action.h"
#include <SPlayerCharacter.h>
#include <SGameplayInterface.h>
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include <SPlayerController.h>

void USFocusOnTarget_Action::ActionStart_Implementation(AActor* Instigator) 
{
	Super::ActionStart_Implementation(Instigator);
	if (TargetActor)
	{
		SetActorToFocus(Instigator);
	}
	else
	{
		GetActorsToFocus(Instigator);
	}
	
}
void USFocusOnTarget_Action::ActionStop_Implementation(AActor* Instigator) 
{
	Super::ActionStop_Implementation(Instigator);
	TargetActor = nullptr;
}

bool USFocusOnTarget_Action::GetActorsToFocus(AActor* Instigator)
{
	TArray<struct FHitResult> OutHits;
	FVector Start;
	FVector End;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionShape CollisionShape;
	float Radius = 200.0f;
	CollisionShape.SetSphere(Radius);
	FCollisionQueryParams Params;
	ASPlayerCharacter* MyCharacter = Cast<ASPlayerCharacter>(Instigator);
	Start = MyCharacter->GetPawnViewLocation();
	End = MyCharacter->GetPawnViewLocation() + (MyCharacter->GetControlRotation().Vector() * 5000);
	Params.AddIgnoredActor(MyCharacter);

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectQueryParams, CollisionShape, Params);

	FColor LineColor = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : OutHits)
	{
		TargetActor = Hit.GetActor();
		return true;
		break;

	}
	
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);
	ASPlayerController* PlayerController = Cast<ASPlayerController>(Instigator->GetInstigatorController());
	PlayerController->SetFocusTarget(false);
	ActionStop_Implementation(Instigator);
	return false;
}

void USFocusOnTarget_Action::SetActorToFocus(AActor* Instigator)
{
	FVector3d PlayerLocation = Instigator->GetActorLocation();

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetActor->GetActorLocation());

	ASPlayerController* PlayerController = Cast<ASPlayerController>(Instigator->GetInstigatorController());

	NewRotation.Roll = PlayerController->GetControlRotation().Roll;
	NewRotation.Pitch = PlayerController->GetControlRotation().Pitch;
		PlayerController->SetControlRotation(NewRotation);
}
