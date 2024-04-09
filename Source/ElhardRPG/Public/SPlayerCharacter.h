// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
UCLASS()
class ELHARDRPG_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere,Category="Camera")
	UCameraComponent* CameraComp;

	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
