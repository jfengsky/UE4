// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/Weapon.h"
#include "Skill/IceStone.h"
#include "Skill/XBlade.h"
#include "PickUp/ItemInfo.h"
#include "XCharacter.generated.h"

/*
 * Ӣ�۽�ɫ��
 */

UCLASS()
class INFINITYBLADE_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*��Ѫ��*/
	UPROPERTY()
	float TotalHP;

	/*��ħ����*/
	UPROPERTY()
	float TotalMP;

	/*��ͨ�����˺�*/
	UPROPERTY()
	float NormalAttack;

public:
	// ���췽��
	AXCharacter();

	/* �������� */
	UPROPERTY()
	class UCameraComponent* CameraComponent;

	/*������*/
	UPROPERTY(EditAnywhere, Category="Weapon")
		TSubclassOf<AWeapon> XWeaponClass;

	/*����������̫��*/
	UPROPERTY(EditAnywhere,Category="Montage")
		class UAnimMontage* SeriorAttackMontage;

	// ����֮ʯ����
	UPROPERTY(EditAnywhere, Category="Skill")
		TSubclassOf<AIceStone> IceStoneClass;

	// �ͷź���֮ʯ����̫��
	UPROPERTY(EditAnywhere,Category="Montage")
	class UAnimMontage* IceStoneMontage;

	// �ָ�������̫��
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* CuteMontage;

	// ����֮����̫��
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* ThunderMontage;

	// �޾�֮����̫��
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* XBladeMontage;

	// �޾�֮������
	UPROPERTY(EditAnywhere, Category="Skill")
	TSubclassOf<AXBlade> XBladeClass;

	// ��Ʒ����
	UPROPERTY()
		TArray<FPickupInfo> PickupArray;

protected:
	// ��Ϸ��ʼ���÷���
	virtual void BeginPlay() override;

	// �ܵ��˺��ķ���
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
