// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMeleeWeaponBase.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UArrowComponent;
UCLASS()
class ELHARDRPG_API ASMeleeWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMeleeWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category="WeaponCollison")
		TObjectPtr <UCapsuleComponent> WeaponCollison;
	UPROPERTY(EditAnywhere,Category="Mesh")
		TObjectPtr<USkeletalMeshComponent> MeshComp;
	UPROPERTY(EditDefaultsOnly,Category="CollisonStart")
	 TObjectPtr<UArrowComponent> CollisonStart;
	UPROPERTY(EditDefaultsOnly,Category="CollisonStop")
	 TObjectPtr<UArrowComponent> CollisonStop;

	UPROPERTY(EditDefaultsOnly,Category="WeaponCollison")
		float Radius = 22.0f;
	UPROPERTY(EditDefaultsOnly,Category="WeaponCollison")
		float HalfHeight = 44.0f;

	bool bISWeapnCollisionActive = false;
	TArray<AActor*> HitActors;
	

	void DrawWeaponCollison();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

		UFUNCTION()
	void StartWeapoCollison();
	UFUNCTION()
	void StopWeapoCollison();
};
