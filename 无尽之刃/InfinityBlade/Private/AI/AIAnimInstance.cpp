// Fill out your copyright notice in the Description page of Project Settings.

#include "AIAnimInstance.h"
#include "AI/MonsterController.h"

/** ���������ƶ��ٶ� */
void UAIAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/** ��ʼ������̫�� */
void UAIAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/** ����������̫�� */
void UAIAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/** ��������֪ͨ */
void UAIAnimInstance::AnimNotify_Death(UAnimNotify* Notify)
{
	AMonsterController* Controller = Cast<AMonsterController>(TryGetPawnOwner()->GetController());
	Controller->AIWeapon->Destroy();
	TryGetPawnOwner()->Destroy();
}

