// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Melee/SMeleeWeaponBase.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Public/KismetTraceUtils.h"
#include "SAttributeComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"

// Sets default values
ASMeleeWeaponBase::ASMeleeWeaponBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	WeaponCollison = CreateDefaultSubobject<UCapsuleComponent>("WeaponCollison");
	RootComponent = WeaponCollison;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(WeaponCollison);

	CollisonStart = CreateDefaultSubobject<UArrowComponent>("CollisonStart");
	CollisonStart->SetupAttachment(MeshComp);

	CollisonStop = CreateDefaultSubobject<UArrowComponent>("CollisonStop");
	CollisonStop->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void ASMeleeWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASMeleeWeaponBase::DrawWeaponCollison()
{
	FVector3d StartWeapon = CollisonStart->GetComponentLocation();
	FVector3d StopWeapon = CollisonStop->GetComponentLocation();

	

	FRotator WeaponRotation = MeshComp->K2_GetComponentRotation();

	TArray<struct FHitResult> WeaponHits;
	FCollisionObjectQueryParams ObjectQueryParams;
	//Change for param that will be filed in BP
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	//Change for param that will be filed in BP
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radius);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetAttachParentActor());

	bool bBlockHit = GetWorld()->SweepMultiByObjectType(WeaponHits, StartWeapon, StopWeapon, FQuat::Identity, ObjectQueryParams, CollisionShape, Params);

	DrawDebugCapsuleTraceMulti(GetWorld(), StartWeapon, StopWeapon, 22, 44, WeaponRotation,
		EDrawDebugTrace::ForOneFrame, bBlockHit, WeaponHits, FColor::Red, FColor::Green, 2.0f);

	/*DrawDebugCapsule(GetWorld(), StartWeapon, 44, 22, FQuat::Identity, FColor::Green, false, 1.0f, 1);*/

	for (FHitResult Hit : WeaponHits)
	{
		if (!HitActors.Contains(Hit.GetActor()))
		{
			HitActors.AddUnique(Hit.GetActor());
			AActor* HitActor = Hit.GetActor();
			USAttributeComponent* AttriComp = Cast<USAttributeComponent>(HitActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		
			if (AttriComp)
			{
				if (AttriComp->CanBeDamaged(HitActor))
				{
					
					AttriComp->ApplyOnHealthChange(-20.0f);
					
				}
			}
		}
	}
}

// Called every frame
void ASMeleeWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bISWeapnCollisionActive)
	{
		DrawWeaponCollison();
	}

}

void ASMeleeWeaponBase::StartWeapoCollison()
{
	bISWeapnCollisionActive = true;
}

void ASMeleeWeaponBase::StopWeapoCollison()
{
	bISWeapnCollisionActive = false;
	HitActors.Empty();
}

