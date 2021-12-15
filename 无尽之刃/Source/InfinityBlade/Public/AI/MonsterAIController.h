// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIAnimInstance.h"
#include "AICharacter.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.generated.h"

/**
 * AI控制器
 */
UCLASS()
class INFINITYBLADE_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// 行为树控件
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComp;

	// 黑板控件
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	/*武器对象*/
	UPROPERTY()
	class AWeapon* AIWeapon;

	// 强转为AI类
	UPROPERTY()
		AAICharacter* Monster;

	//	AI动画实例
	UPROPERTY()
		UAIAnimInstance* AnimInstance;

public:

	// 构造方法
	AMonsterAIController();

	// 重写控制的方法
		virtual void OnPossess(APawn* InPawn) override;

	// 武器伤害
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
