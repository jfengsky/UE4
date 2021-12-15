// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceStone.generated.h"

/**
* 寒冰之石技能
*/
UCLASS()
class INFINITYBLADE_API AIceStone : public AActor
{
	GENERATED_BODY()

public:

	// 粒子系统
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;

	//胶囊体组件
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

	// 子弹移动组件
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComp;

	// 爆炸粒子特效
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplodeParticle;

	// 技能击中的声音
	UPROPERTY(EditAnywhere, Category = "Particle Sound")
	USoundBase* ExplodeSound;
public:	
	// 构造方法
	AIceStone();

protected:
	// 游戏开始调用的方法
	virtual void BeginPlay() override;

public:
	// 发射方法
	void Shoot(FVector Direction);
	
	// 击中方法
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
