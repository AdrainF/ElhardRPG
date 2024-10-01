// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USActionComponent;
class USAttributeComponent;
class USInteractionComponent;
UCLASS()
class ELHARDRPG_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category = "Attribute")
		USAttributeComponent* AttriComp;
	UPROPERTY(EditDefaultsOnly, Category = "Interact")
		USInteractionComponent* InteractComp;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		USActionComponent* ActionComp;

	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
		USActionComponent* GetActionComponent();
	UFUNCTION(BlueprintCallable)
		USpringArmComponent* GetCameraBoom();
	UFUNCTION(BlueprintCallable)
		USInteractionComponent* GetInteractionComponent();


	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
