// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 *
 */
class UInputAction;
class UInputMappingContext;
class ASPlayerCharacter;
class UEnhancedInputComponent;

UCLASS()
class ELHARDRPG_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionMove")
		UInputAction* ActionMove = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionLook")
		UInputAction* ActionLook = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionJump")
		UInputAction* ActionJump = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionPrimaryAttack")
		UInputAction* ActionPrimaryAttack = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput MappingContext")
		TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;
protected:
	// Used to store reference to controlled player pawn
	UPROPERTY()
		ASPlayerCharacter* PlayerChar = nullptr;
	// Used to store a reference to the InputComponent cast to an EnhancedInputComponent.
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
		UEnhancedInputComponent* EnhancedInputComp = nullptr;

	virtual void OnPossess(APawn* aPawn) override;

	//Input handler functions
	UFUNCTION()
		void HandlerMove(const FInputActionValue& Value);
	UFUNCTION()
		void HandlerLook(const FInputActionValue& Value);
	UFUNCTION()
		void HandlerJump();
	UFUNCTION()
		void HandlerPrimaryAttack();


};
