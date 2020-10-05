// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "PlayingCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//TryGetPawnOwner() ���ص���һ��Pawn�࣬��ͨ������ģ���������ָ�������Ľ�ɫ��Ȼ���ٰѷ��ص�Pawnת����������Ҫ�Ľ�ɫ
	APlayingCharacter* Character = Cast<APlayingCharacter>(TryGetPawnOwner());
	if (Character) {
		//GetVelocity() ���ص��ǽ�ɫ���ƶ�������ٶ�,������ֵ����0˵��Character���ƶ�,Size() �ǻ�ȡ������ģ
		IsMove = Character->GetVelocity().Size();

		//IsFalling()  �����ɫ��ǰ�����½��ͷ�����
		IsJump = Character->GetCharacterMovement()->IsFalling();
	}
}