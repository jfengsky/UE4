// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterPlayerController::ACharacterPlayerController()
{
}

void ACharacterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("CharacterMoveType", IE_Pressed, this, &ACharacterPlayerController::CharacterMoveTypeChange);
}

void ACharacterPlayerController::CharacterMoveTypeChange()
{
	ABasicCharacter* Ch = Cast<ABasicCharacter>(GetCharacter());
	if(Ch)
	{
		UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(Ch->GetMesh()->GetAnimInstance());
		if(AnimInstance)
		{
			switch(AnimInstance->MoveSpeed)
			{
				case 0:
					AnimInstance->MoveSpeed = 1.0f;
					Ch->GetCharacterMovement()->MaxWalkSpeed = 900;
					break;
				case 1:
					AnimInstance->MoveSpeed = 2.0f;
					Ch->GetCharacterMovement()->MaxWalkSpeed = 1100;
					break;
				case 2:
					AnimInstance->MoveSpeed = 0;
					Ch->GetCharacterMovement()->MaxWalkSpeed = 700;
			}
		}
	}
}
