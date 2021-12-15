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
 * 英雄角色类
 */

UCLASS()
class INFINITYBLADE_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*总血量*/
	UPROPERTY()
	float TotalHP;

	/*总魔法量*/
	UPROPERTY()
	float TotalMP;

	/*普通攻击伤害*/
	UPROPERTY()
	float NormalAttack;

public:
	// 构造方法
	AXCharacter();

	/* 摄像机组件 */
	UPROPERTY()
	class UCameraComponent* CameraComponent;

	/*武器类*/
	UPROPERTY(EditAnywhere, Category="Weapon")
		TSubclassOf<AWeapon> XWeaponClass;

	/*连击动画蒙太奇*/
	UPROPERTY(EditAnywhere,Category="Montage")
		class UAnimMontage* SeriorAttackMontage;

	// 寒冰之石类型
	UPROPERTY(EditAnywhere, Category="Skill")
		TSubclassOf<AIceStone> IceStoneClass;

	// 释放寒冰之石的蒙太奇
	UPROPERTY(EditAnywhere,Category="Montage")
	class UAnimMontage* IceStoneMontage;

	// 恢复技能蒙太奇
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* CuteMontage;

	// 雷霆之光蒙太奇
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* ThunderMontage;

	// 无尽之刃蒙太奇
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* XBladeMontage;

	// 无尽之刃类型
	UPROPERTY(EditAnywhere, Category="Skill")
	TSubclassOf<AXBlade> XBladeClass;

	// 物品数组
	UPROPERTY()
		TArray<FPickupInfo> PickupArray;

protected:
	// 游戏开始调用方法
	virtual void BeginPlay() override;

	// 受到伤害的方法
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
