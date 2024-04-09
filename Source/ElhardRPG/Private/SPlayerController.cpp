// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"
#include "SPlayerCharacter.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>

void ASPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	// Store a reference to the Player's Pawn
	PlayerChar = Cast<ASPlayerCharacter>(aPawn);
	checkf(PlayerChar, TEXT("Controller should only possess the ASPlayerCharacter class"));

	//Get a reference to the EnhancedInputComponent
	EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComp, TEXT("Unable to get reference to EnhancedInputComponent"));

	//Get local Player subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	checkf(InputMappingContext, TEXT("InputMappingContex was not specified"));

	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext,0);

	if (ActionMove)
	{
		EnhancedInputComp->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerMove);
	}
	if (ActionLook)
	{
		EnhancedInputComp->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerLook);
	}
	if (ActionJump)
	{
		EnhancedInputComp->BindAction(ActionJump, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerJump);
	}


}

void ASPlayerController::HandlerMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	//Get controller forward rotation
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	//Get controller right rotation
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	if (PlayerChar)
	{
		PlayerChar->AddMovementInput(ControlRot.Vector(),MovementVector.Y);
		PlayerChar->AddMovementInput(RightVector, MovementVector.X);
	}
	

}

void ASPlayerController::HandlerLook(const FInputActionValue& Value)
{
	FVector2D ControllerVector = Value.Get<FVector2D>();

	if (PlayerChar)
	{
		PlayerChar->AddControllerPitchInput(ControllerVector.Y);
		PlayerChar->AddControllerYawInput(ControllerVector.X);
	}
}

void ASPlayerController::HandlerJump()
{
	if (PlayerChar)
	{
		PlayerChar->Jump();
	}

}
