// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/Weapon.h"
#include "AI/AIAnimInstance.h"
#include "AI/AICharacter.h"
#include "MonsterController.generated.h"

/**
 * AI������
 */
UCLASS()
class INFINITYBLADE_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	/** ��Ϊ���ؼ� */
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent;
	/** �ڰ�ؼ� */
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent;
	/** �������� */
	UPROPERTY()
		AWeapon* AIWeapon;
	/** AI�� */
	UPROPERTY()
		AAICharacter* Monster;
	/** AI����ʵ�� */
	UPROPERTY()
		UAIAnimInstance* AnimInstance;
public:
	/** ���췽�� */
	AMonsterController();
	/** ��д���Ƶķ��� */
	virtual void Possess(APawn* InPawn) override;
	/** �����ص��˺��¼� */
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);
};
