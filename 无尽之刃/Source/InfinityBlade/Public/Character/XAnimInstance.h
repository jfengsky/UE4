// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "XPlayerState.h"
#include "XAnimInstance.generated.h"

/**
 * 英雄角色的的动画实例
 */
UCLASS()
class INFINITYBLADE_API UXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/*橘色状态*/
	UPROPERTY()
	AXPlayerState* XPlayState;

	/* 人物移动速度*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Speed;

	// 是否处于攻击状态
	bool bIsAttacking;

	/*角色的基本攻击*/
	float NormalAttack;

	/*是否处于播放状态*/
	bool bIsPlaying;

	/*是否进入第二次连击*/
	bool bIsEnableSecondAttack;

	/*是否进入第三次连击*/
	bool bIsEnableThreeAttack;

	/*是否进入第四次连击*/
	bool bIsEnableFourAttack;

	/*是否进入第五次连击*/
	bool bIsEnableFiveAttack;

	// 是否释放了无尽之刃技能
	bool bIsPlayXBlade;

	// 无尽之刃定时器
	UPROPERTY()
		FTimerHandle TimerHandle;

	TArray<FName> AttackSections{FName("FirstAttack"), FName("SecondAttack"), FName("ThreeAttack") ,FName("FourAttack") ,FName("FiveAttack") };

public:
	/*重写初始化方法*/
	//virtual void NativeInitializeAnimation() override;

public:

	/*开始播放蒙太奇动画通知*/
	UFUNCTION()
		void AnimNotify_PlayStart(UAnimNotify* Notify);

	/*结束播放蒙太奇动画通知*/
	UFUNCTION()
		void AnimNotify_PlayEnd(UAnimNotify* Notify);

	/*开始计算攻击的动画通知*/
	UFUNCTION()
		void AnimNotify_AttackStart(UAnimNotify* Notify);

	/*结束计算攻击的动画通知*/
	UFUNCTION()
		void AnimNotify_AttackEnd(UAnimNotify* Notify);
	
	/*重置连击状态*/
	UFUNCTION()
		void AnimNotify_ResetSerialAttack(UAnimNotify* Notify);

	/*进入第二次连击*/
	UFUNCTION()
		void AnimNotify_SecondAttackInput(UAnimNotify* Notify);

	/*进入第三次连击*/
	UFUNCTION()
		void AnimNotify_ThreeAttackInput(UAnimNotify* Notify);

	/*进入第四次连击*/
	UFUNCTION()
		void AnimNotify_FourAttackInput(UAnimNotify* Notify);

	/*进入第五次连击*/
	UFUNCTION()
		void AnimNotify_FiveAttackInput(UAnimNotify* Notify);

	// 寒冰之石技能产生通知
	UFUNCTION()
	void AnimNotify_SpawnIceStone(UAnimNotify* Notify);

	// 恢复技能产生通知
	UFUNCTION()
	void AnimNotify_Cure(UAnimNotify* Notify);

	// 雷霆之光技能通知
	UFUNCTION()
	void AnimNotify_Thunder(UAnimNotify* Notify);

	// 无尽之刃技能通知
	UFUNCTION()
	void AnimNotify_XBlade(UAnimNotify* Notify);

	// 无尽之刃技能结束,定时器回调
	void TimerCallback();

	/*初始化玩家状态*/
	void InitState();

	/*重置为普通攻击*/
	void ResetNormalAttack();

	/*连击加成伤害*/
	void UpdateSerialAttack();

	// 扣除魔法值
	void MinusMP(float MP);

	// 更新MPUI
	UFUNCTION()
		void UpDateMP();
	
public:

	/*更新人物移动速度*/
	UFUNCTION(BlueprintCallable)
		void UpDateSpeed();
};
