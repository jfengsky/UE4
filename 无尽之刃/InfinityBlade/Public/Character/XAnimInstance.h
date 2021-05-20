// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/XPlayerState.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "XAnimInstance.generated.h"

/**
 * Ӣ�۽�ɫ�Ķ���ʵ��
 */
UCLASS()
class INFINITYBLADE_API UXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/** ��ɫ״̬ */
	UPROPERTY()
		AXPlayerState* XPlayerState;
	/** ��ɫ�Ļ������� */
	float NormalAttack;

	/** ������ƶ��ٶ� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

	/** �Ƿ��ڹ���״̬ */
	bool bIsAttacking;
	/** �Ƿ��ڲ���״̬ */
	bool bIsPlaying;
	/** �Ƿ����ڶ������� */
	bool bIsEnableSecondAttack;
	/** �Ƿ������������� */
	bool bIsEnableThreeAttack;
	/** �Ƿ������Ĵ����� */
	bool bIsEnableFourAttack;
	/** �Ƿ������������ */
	bool bIsEnableFiveAttack;

	/** �Ƿ��ͷ��޾�֮�м��� */
	bool bIsXBlade;
	/** �޾�֮�ж�ʱ�� */
	UPROPERTY()
		FTimerHandle TimerHandle;

public:
	/** ���������ƶ��ٶ� */
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();

public:
	/** ��ʼ������̫�� */
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);
	/** ����������̫�� */
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);

	/** ��ʼ������̫�� */
	UFUNCTION()
		void AnimNotify_AttackStart(UAnimNotify* Notify);
	/** ����������̫�� */
	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify* Notify);

	/** ��������״̬ */
	UFUNCTION()
		void AnimNotify_ResetSerialAttack(UAnimNotify* Notify);
	/** ����ڶ������� */
	UFUNCTION()
		void AnimNotify_SecondAttackInput(UAnimNotify* Notify);
	/** ������������� */
	UFUNCTION()
		void AnimNotify_ThreeAttackInput(UAnimNotify* Notify);
	/** ������Ĵ����� */
	UFUNCTION()
		void AnimNotify_FourAttackInput(UAnimNotify* Notify);
	/** ������������ */
	UFUNCTION()
		void AnimNotify_FiveAttackInput(UAnimNotify* Notify);

	/** ��ʼ�����״̬ */
	void InitState();
	/** ����Ϊ��ͨ���� */
	void ResetNormalAttack();
	/** ���мӳ��˺� */
	void UpdateSerialAttack();
	/** �۳�ħ��ֵ */
	void MinusMP(float MP);
	/** ����MP��UI */
	void UpdateMPUI();

	/** ����֮ʯ����֪ͨ */
	UFUNCTION()
		void AnimNotify_SpawnIceStone(UAnimNotify* Notify);
	/** �ָ�֮������֪ͨ */
	UFUNCTION()
		void AnimNotify_UseCure(UAnimNotify* Notify);
	/** ����֮�����֪ͨ */
	UFUNCTION()
		void AnimNotify_UseThunder(UAnimNotify* Notify);
	/** �޾�֮�в���֪ͨ */
	UFUNCTION()
		void AnimNotify_SpawnXBlade(UAnimNotify* Notify);
	/** ��ʱ���ص����� */
	void TimerCallback();
};
