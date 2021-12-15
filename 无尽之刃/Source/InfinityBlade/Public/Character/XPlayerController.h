// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerState.h"
#include "XPlayerController.generated.h"

/**
 * 主角英雄的控制器
 */
UCLASS()
class INFINITYBLADE_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/* 角色对象 */
	UPROPERTY()
	class AXCharacter* XCharacter;

	/*角色状态*/
	UPROPERTY()
		AXPlayerState* XPlayerState;

	/*英雄角色动画实例*/
	UPROPERTY()
	class UXAnimInstance* XAnimInstance;

	UPROPERTY()
	TArray<AActor*> AiArray;

	// 寒冰之石技能冷却定时器
	FTimerHandle IceStoneTimer;

	// 寒冰之石技能当前冷却时间
	float IceStoneCurrentCD;

	// 寒冰之石技能总共冷却时间
	float IceStoneTotalCD;
	
public:

	/*主界面UI*/
	UPROPERTY()
		class UMainUserWidget* MainWidget;

	/*初始化人物信息界面*/
	UPROPERTY()
	class UCharacterWidget *CharacterWidget;

	/*武器对象*/
	UPROPERTY()
		class AWeapon* XWeapon;

public:
	/* 游戏开始调用的方法 */
	virtual void BeginPlay() override;

	/* 绑定输入控件 */
	virtual void SetupInputComponent() override;

	/*前后移动*/
	UFUNCTION()
		void MoveForward(float Speed);

	/*左右移动*/
	UFUNCTION()
		void MoveRight(float Speed);

	/* 控件按钮初始化事件方法 */
	UFUNCTION()
		void InitWidgetEvent();

	/*攻击按钮点击事件*/
	UFUNCTION()
		void AttackBtnOnClickedEvent();

	// 释放寒冰之石技能
	UFUNCTION()
		void IceStoneBtnOnClickedEvent();

	// 寒冰之石冷却回调方法
	void IceStoneCallback();

	// 恢复技能
	UFUNCTION()
		void CureBtnOnclickedEvent();

	// 释放雷霆之光技能
	UFUNCTION()
		void ThunderBtnOnClickedEvent();

	// 释放无尽之刃技能
	UFUNCTION()
		void XBladeBtnOnClickedEvent();
	
	/*初始化玩家状态*/
	UFUNCTION()
	void InitState();

	/*初始化UI*/
	UFUNCTION()
	void InitUI();

	// 武器伤害
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// 锁定敌人
	UFUNCTION()
	void LockAI();

	// 人物角色信息点击事件
	UFUNCTION()
		void CharacterBtnOnClickedEvent();
};
