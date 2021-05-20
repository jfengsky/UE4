// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Character/Skill/IceStone.h"
#include "Character/Skill/XBlade.h"
#include "Pickup/ItemInfo.h"
#include "XCharacter.generated.h"

/** 
 * Ӣ�۽�ɫ��
 */
UCLASS()
class INFINITYBLADE_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** �������� */
	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComponent;
	/** ������ */
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<AWeapon> XWeaponClass;
public:
	/** ��Ѫ�� */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float TotalHP;
	/** ��ħ���� */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float TotalMP;
	/** ��ͨ�����˺� */
	UPROPERTY(EditAnywhere, Category = "PlayerState")
		float NoramlAttack;
	/** ����������̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* SerialAttackMontage;

	/** ����֮ʯ���� */
	UPROPERTY(EditAnywhere, Category = "Skill")
		TSubclassOf<AIceStone> IceStoneClass;
	/** ����֮ʯ��̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* IceStoneMontage;
	/** �ָ�֮����̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* CureMontage;
	/** ����֮����̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* ThunderMontage;
	/** �޾�֮������ */
	UPROPERTY(EditAnywhere, Category = "Skill")
		TSubclassOf<AXBlade> XBladeClass;
	/** �޾�֮����̫�� */
	UPROPERTY(EditAnywhere, Category = "Montage")
		UAnimMontage* XBladeMontage;

	/** ��Ʒ���� */
	UPROPERTY()
		TArray<FPickupInfo> PickupArray;

public:
	/** ���췽�� */
	AXCharacter();

protected:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;	
	/** �ܵ��˺��ķ��� */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
