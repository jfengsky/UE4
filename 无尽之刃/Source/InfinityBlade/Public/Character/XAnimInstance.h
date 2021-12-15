// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "XPlayerState.h"
#include "XAnimInstance.generated.h"

/**
 * Ӣ�۽�ɫ�ĵĶ���ʵ��
 */
UCLASS()
class INFINITYBLADE_API UXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/*��ɫ״̬*/
	UPROPERTY()
	AXPlayerState* XPlayState;

	/* �����ƶ��ٶ�*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

	// �Ƿ��ڹ���״̬
	bool bIsAttacking;

	/*��ɫ�Ļ�������*/
	float NormalAttack;

	/*�Ƿ��ڲ���״̬*/
	bool bIsPlaying;

	/*�Ƿ����ڶ�������*/
	bool bIsEnableSecondAttack;

	/*�Ƿ�������������*/
	bool bIsEnableThreeAttack;

	/*�Ƿ������Ĵ�����*/
	bool bIsEnableFourAttack;

	/*�Ƿ������������*/
	bool bIsEnableFiveAttack;

	// �Ƿ��ͷ����޾�֮�м���
	bool bIsPlayXBlade;

	// �޾�֮�ж�ʱ��
	UPROPERTY()
		FTimerHandle TimerHandle;

	TArray<FName> AttackSections{FName("FirstAttack"), FName("SecondAttack"), FName("ThreeAttack") ,FName("FourAttack") ,FName("FiveAttack") };

public:
	/*��д��ʼ������*/
	//virtual void NativeInitializeAnimation() override;

public:

	/*��ʼ������̫�涯��֪ͨ*/
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);

	/*����������̫�涯��֪ͨ*/
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);

	/*��ʼ���㹥���Ķ���֪ͨ*/
	UFUNCTION()
		void AnimNotify_AttackStart(UAnimNotify* Notify);

	/*�������㹥���Ķ���֪ͨ*/
	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify* Notify);
	
	/*��������״̬*/
	UFUNCTION()
		void AnimNotify_ResetSerialAttack(UAnimNotify* Notify);

	/*����ڶ�������*/
	UFUNCTION()
		void AnimNotify_SecondAttackInput(UAnimNotify* Notify);

	/*�������������*/
	UFUNCTION()
		void AnimNotify_ThreeAttackInput(UAnimNotify* Notify);

	/*������Ĵ�����*/
	UFUNCTION()
		void AnimNotify_FourAttackInput(UAnimNotify* Notify);

	/*������������*/
	UFUNCTION()
		void AnimNotify_FiveAttackInput(UAnimNotify* Notify);

	// ����֮ʯ���ܲ���֪ͨ
	UFUNCTION()
	void AnimNotify_SpawnIceStone(UAnimNotify* Notify);

	// �ָ����ܲ���֪ͨ
	UFUNCTION()
	void AnimNotify_Cure(UAnimNotify* Notify);

	// ����֮�⼼��֪ͨ
	UFUNCTION()
	void AnimNotify_Thunder(UAnimNotify* Notify);

	// �޾�֮�м���֪ͨ
	UFUNCTION()
	void AnimNotify_XBlade(UAnimNotify* Notify);

	// �޾�֮�м��ܽ���,��ʱ���ص�
	void TimerCallback();

	/*��ʼ�����״̬*/
	void InitState();

	/*����Ϊ��ͨ����*/
	void ResetNormalAttack();

	/*�����ӳ��˺�*/
	void UpdateSerialAttack();

	// �۳�ħ��ֵ
	void MinusMP(float MP);

	// ����MPUI
	UFUNCTION()
		void UpDateMP();
	
public:

	/*���������ƶ��ٶ�*/
	UFUNCTION(BlueprintCallable)
		void UpDateSpeed();
};
