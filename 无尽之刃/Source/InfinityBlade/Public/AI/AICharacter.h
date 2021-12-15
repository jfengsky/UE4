// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Weapon/Weapon.h"
#include "AICharacter.generated.h"

/**
 * ������
 */
UCLASS()
class INFINITYBLADE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*���췽��*/
	AAICharacter();

public:
	/*UI���*/
	UPROPERTY(VisibleAnywhere)
	 class UWidgetComponent* WidgetComp;

	// Ѫ��
	float TotalHP;

	// ��ǰѪ��
	float CurrentHP;

	bool bIsDead;

	/*������*/
	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<AWeapon> AIWeaponClass;
	
	/*Ѫ��Widget*/
	UPROPERTY()
		UProgressBar* HPBar;

	UPROPERTY()
		UTextBlock* CurrentHPText;

	// ��Ϊ������
	UPROPERTY(EditAnywhere, Category="AI")
		UBehaviorTree* BehaviorTree;

	// ����������̫������
	UPROPERTY(EditAnywhere, Category="Montage")
		TArray<UAnimMontage*> AttackMontages;

	// ���˶�����̫��
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* DamageMontage;

	// ����������̫��
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* DeathMontage;

protected:
	// ��Ϸ��ʼ���õķ���
	virtual void BeginPlay() override;

	/*��д�ܵ��˺��ķ���*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
