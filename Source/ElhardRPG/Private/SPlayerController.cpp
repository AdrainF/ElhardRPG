// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"
#include "SPlayerCharacter.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "SActionComponent.h"
#include "SAction.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "KismetTraceUtils.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"


void ASPlayerController::SetFocusTarget(bool Value)
{
	bFocusTarget = Value;
}

bool ASPlayerController::GetIsBlocking()
{
	return bIsBlocking;
}



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
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

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
	if (ActionPrimaryAttack)
	{
		EnhancedInputComp->BindAction(ActionPrimaryAttack, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerPrimaryAttack);
	}
	if (ActionBasicAttack)
	{
		EnhancedInputComp->BindAction(ActionBasicAttack, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerBasicAttack);
	}
	if (ActionMoveReleas)
	{
		EnhancedInputComp->BindAction(ActionMoveReleas, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerMoveReleas);
	}
	if (ActionPrimaryInteract)
	{
		EnhancedInputComp->BindAction(ActionPrimaryInteract, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerPrimaryInteract);
	}
	if (ActionFocusTarget)
	{
		EnhancedInputComp->BindAction(ActionFocusTarget, ETriggerEvent::Triggered, this, &ASPlayerController::HandlerFocusTarget);
	}
	if (ActionBlock)
	{
		EnhancedInputComp->BindAction(ActionBlock, ETriggerEvent::Started, this, &ASPlayerController::HandlerBlockStart);
		EnhancedInputComp->BindAction(ActionBlock, ETriggerEvent::Completed, this, &ASPlayerController::HandlerBlockStop);
	}
	if (ActionDodge)
	{
		EnhancedInputComp->BindAction(ActionDodge, ETriggerEvent::Started, this, &ASPlayerController::HandlerDodge);
		
	}

}

void ASPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bFocusTarget)
	{
		PlayerChar->GetActionComponent()->StartActionByName(PlayerChar, "FocusTarget");
	}
	else
	{
		PlayerChar->GetActionComponent()->StopActionByName(PlayerChar, "FocusTarget");

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
		//Adding Tags
		PlayerChar->GetActionComponent()->StartActionByName(PlayerChar, "Move");
		//Getting Action reference
		USAction* MyAction = PlayerChar->GetActionComponent()->GetActionByName("Move");

		//Check if we have no blocking tags
		if (MyAction && MyAction->CanStart_Implementation(PlayerChar))
		{
			PlayerChar->AddMovementInput(ControlRot.Vector(), MovementVector.Y);
			PlayerChar->AddMovementInput(RightVector, MovementVector.X);
		}
	}

}

void ASPlayerController::HandlerMoveReleas(const FInputActionValue& Value)
{
	if (PlayerChar)
	{
		PlayerChar->GetActionComponent()->StopActionByName(PlayerChar, "Move");
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

void ASPlayerController::HandlerPrimaryAttack()
{
	if (PlayerChar)
	{
		PlayerChar->GetActionComponent()->StartActionByName(PlayerChar, "PrimaryAttack");
	}
}

void ASPlayerController::HandlerBasicAttack()
{
	if (PlayerChar)
	{
		PlayerChar->GetActionComponent()->StartActionByName(PlayerChar, "BasicAttack");
	
	}
}

void ASPlayerController::HandlerPrimaryInteract()
{
	if (PlayerChar)
	{
		PlayerChar->GetInteractionComponent()->PrimaryInteract();
	}
}

void ASPlayerController::HandlerFocusTarget()
{
	if (!bFocusTarget)
	{
		bFocusTarget = true;
	}
	else
	{
		bFocusTarget = false;
	}
}

void ASPlayerController::HandlerBlockStart()
{
	
	bIsBlocking = true;
}

void ASPlayerController::HandlerBlockStop()
{
	bIsBlocking = false;
}

void ASPlayerController::HandlerDodge()
{
	if (PlayerChar)
	{
		PlayerChar->GetActionComponent()->StartActionByName(PlayerChar, "Dodge");
	}
}
