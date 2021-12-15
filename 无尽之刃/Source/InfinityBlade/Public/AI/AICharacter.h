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
 * 怪物类
 */
UCLASS()
class INFINITYBLADE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/*构造方法*/
	AAICharacter();

public:
	/*UI组件*/
	UPROPERTY(VisibleAnywhere)
	 class UWidgetComponent* WidgetComp;

	// 血量
	float TotalHP;

	// 当前血量
	float CurrentHP;

	bool bIsDead;

	/*武器类*/
	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<AWeapon> AIWeaponClass;
	
	/*血条Widget*/
	UPROPERTY()
		UProgressBar* HPBar;

	UPROPERTY()
		UTextBlock* CurrentHPText;

	// 行为树对象
	UPROPERTY(EditAnywhere, Category="AI")
		UBehaviorTree* BehaviorTree;

	// 攻击动画蒙太奇数组
	UPROPERTY(EditAnywhere, Category="Montage")
		TArray<UAnimMontage*> AttackMontages;

	// 受伤动画蒙太奇
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* DamageMontage;

	// 死亡动画蒙太奇
	UPROPERTY(EditAnywhere, Category="Montage")
	class UAnimMontage* DeathMontage;

protected:
	// 游戏开始调用的方法
	virtual void BeginPlay() override;

	/*重写受到伤害的方法*/
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
