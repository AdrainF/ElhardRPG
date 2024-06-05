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
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionMove")
		UInputAction* ActionMoveReleas = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionLook")
		UInputAction* ActionLook = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionJump")
		UInputAction* ActionJump = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionPrimaryAttack")
		UInputAction* ActionPrimaryAttack = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionPrimaryAttack")
		UInputAction* ActionPrimaryInteract = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionFocusTarget")
		UInputAction* ActionFocusTarget = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput Action | ActionBlock")
		UInputAction* ActionBlock = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput MappingContext")
		TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;
	UFUNCTION(BlueprintCallable)
		void SetFocusTarget(bool Value);
	UFUNCTION(BlueprintCallable)
		bool GetIsBlocking();
	

protected:
	// Used to store reference to controlled player pawn
	UPROPERTY()
		ASPlayerCharacter* PlayerChar = nullptr;
	// Used to store a reference to the InputComponent cast to an EnhancedInputComponent.
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
		UEnhancedInputComponent* EnhancedInputComp = nullptr;
	//Check if we are focusing on the target
	bool bFocusTarget = false;
	bool bIsBlocking = false;
	

	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime);

	//Input handler functions
	UFUNCTION()
		void HandlerMove(const FInputActionValue& Value);
	UFUNCTION()
		void HandlerMoveReleas(const FInputActionValue& Value);
	UFUNCTION()
		void HandlerLook(const FInputActionValue& Value);
	UFUNCTION()
		void HandlerJump();
	UFUNCTION()
		void HandlerPrimaryAttack();
	UFUNCTION()
		void HandlerPrimaryInteract();
	UFUNCTION()
		void HandlerFocusTarget();
	UFUNCTION()
		void HandlerBlockStart();
	UFUNCTION()
		void HandlerBlockStop();


};
