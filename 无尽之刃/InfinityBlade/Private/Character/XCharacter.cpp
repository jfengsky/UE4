// Fill out your copyright notice in the Description page of Project Settings.

#include "XCharacter.h"
#include "Character/XPlayerController.h"
#include "Character/XPlayerState.h"

/** ���췽�� */
AXCharacter::AXCharacter()
{
	/** ���ý�ɫ�ƶ��ĳ��� */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	/** ���ý�ɫ�������Ƿ���Ƴ��� */
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
 	/** ��ʼ�������� */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CamerComponent");
	/** �������󶨸���� */
	CameraComponent->SetupAttachment(RootComponent);
	/** �����ɫ���������Ƴ��� */
	CameraComponent->bUsePawnControlRotation = false;
}

/** ��Ϸ��ʼ���õķ��� */
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

/** �ܵ��˺��ķ��� */
float AXCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	AXPlayerController* Controller = Cast<AXPlayerController>(GetController());
	AXPlayerState* PlayerState = Controller->XPlayerState;
	PlayerState->SetCurrentHP(PlayerState->GetCurrentHP() - Damage);
	Controller->UpdateUI();

	return Damage;
}

