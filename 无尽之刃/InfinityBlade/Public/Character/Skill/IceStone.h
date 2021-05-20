// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "IceStone.generated.h"

/**
 * ����֮ʯ
 */
UCLASS()
class INFINITYBLADE_API AIceStone : public AActor
{
	GENERATED_BODY()
	
public:
	/** ����ϵͳ��� */
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ParticleSystemComponent;
	/** ��������� */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;
	/** �ӵ��ƶ���� */
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovementComponent;
	/** ��ը������Ч */
	UPROPERTY(EditAnywhere, Category = "Particle")
		UParticleSystem* ExplodeParticle;
	/** ��ը�������� */
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* ExplodeSound;
public:	
	/** ���췽�� */
	AIceStone();
	/** ���䷽�� */
	void Shoot(FVector Direction);
protected:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;
	/** �����¼� */
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);
};
