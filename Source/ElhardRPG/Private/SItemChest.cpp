// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

ASItemChest::ASItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(110.0f, 0.0f, 0.0f));
}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

