// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SItemChest.generated.h"

UCLASS()
class ELHARDRPG_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	ASItemChest();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* LidMesh;

	void Interact_Implementation(APawn* InstigatorPawn);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
