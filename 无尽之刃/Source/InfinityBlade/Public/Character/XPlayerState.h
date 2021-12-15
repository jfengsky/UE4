// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "XPlayerState.generated.h"

/**
 * 玩家状态
 */
UCLASS()
class INFINITYBLADE_API AXPlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	
	/*当前血量*/
	float CurrentHP;

	/*当前魔法值*/
	float CurrentMP;

	/*普通攻击伤害*/
	float AttackDamage;
public:

	/*设置当前血量*/
	FORCEINLINE void SetCurrentHP(float hp) { this->CurrentHP = hp; };

	/*获取当前血量*/
	FORCEINLINE float GetCurrentHP() { return CurrentHP; };

	/*设置当前魔法值*/
	FORCEINLINE void SetCurrentMP(float mp) { this->CurrentMP = mp; };

	/*获取当前魔法值*/
	FORCEINLINE float GetCurrentMP() { return CurrentMP; };

	/*设置攻击伤害*/
	FORCEINLINE void SetAttackDamage(float AttackDmg) { this->AttackDamage = AttackDmg; };

	/* 返回攻击伤害 */
	FORCEINLINE float GetAttackDamage() { return AttackDamage; };
};
