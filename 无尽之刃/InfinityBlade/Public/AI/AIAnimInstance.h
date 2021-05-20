// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

/**
 * AI����ʵ��
 */
UCLASS()
class INFINITYBLADE_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/** ������ƶ��ٶ� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;
	/** �Ƿ��ڲ���״̬ */
	bool bIsPlaying;
public:
	/** ���������ƶ��ٶ� */
	UFUNCTION(BlueprintCallable)
		void UpdateSpeed();
	/** ��ʼ����֪ͨ */
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);
	/** ��������֪ͨ */
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);
	/** ��������֪ͨ */
	UFUNCTION()
		void AnimNotify_Death(UAnimNotify* Notify);
};
