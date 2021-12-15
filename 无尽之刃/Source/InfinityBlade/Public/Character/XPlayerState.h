// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "XPlayerState.generated.h"

/**
 * ���״̬
 */
UCLASS()
class INFINITYBLADE_API AXPlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	
	/*��ǰѪ��*/
	float CurrentHP;

	/*��ǰħ��ֵ*/
	float CurrentMP;

	/*��ͨ�����˺�*/
	float AttackDamage;
public:

	/*���õ�ǰѪ��*/
	FORCEINLINE void SetCurrentHP(float hp) { this->CurrentHP = hp; };

	/*��ȡ��ǰѪ��*/
	FORCEINLINE float GetCurrentHP() { return CurrentHP; };

	/*���õ�ǰħ��ֵ*/
	FORCEINLINE void SetCurrentMP(float mp) { this->CurrentMP = mp; };

	/*��ȡ��ǰħ��ֵ*/
	FORCEINLINE float GetCurrentMP() { return CurrentMP; };

	/*���ù����˺�*/
	FORCEINLINE void SetAttackDamage(float AttackDmg) { this->AttackDamage = AttackDmg; };

	/* ���ع����˺� */
	FORCEINLINE float GetAttackDamage() { return AttackDamage; };
};
