// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Weapon/Weapon.h"
#include "AICharacter.generated.h"

/**
 * AI������
 */
UCLASS()
class INFINITYBLADE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** UI��� */
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* WidgetComponent;
	/** Ѫ�� */
	UPROPERTY(EditAnywhere, Category = "State")
		float TotalHP;
	/** ��ǰѪ�� */
	float CurrentHP;
	/** �Ƿ����� */
	bool bIsDead;
	/** Ѫ��Widget */
	UPROPERTY()
		UProgressBar* HPBar;
	/** ��Ϊ������ */
	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree;
	/** ������ */
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<AWeapon> AIWeaponClass;
	/** ����������̫������ */
	UPROPERTY(EditAnywhere, Category = "Montage")
		TArray<UAnimMontage*> AttackMontages;
	/** ���˶�����̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* DamageMontage;
	/** ����������̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* DeathMontage;
public:
	/** ���췽�� */
	AAICharacter();

protected:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;
	/** ��д�յ��˺��ķ��� */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
