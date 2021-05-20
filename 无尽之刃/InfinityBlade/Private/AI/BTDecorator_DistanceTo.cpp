// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_DistanceTo.h"
#include "AI/MonsterController.h"
#include "AI/AICharacter.h"

/** ��д�жϵķ��� */
bool UBTDecorator_DistanceTo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	/** ��ȡController */
	AMonsterController* Controller = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	/** ��ȡAI */
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	/** ��ȡ�ڰ�ؼ� */
	UBlackboardComponent* Blackboard = Controller->BlackboardComponent;

	/** ��ȡĿ��λ�� */
	FVector TargetLocation = Blackboard->GetValueAsVector(TEXT("TargetLocation"));
	/** ��ȡ���߾��� */
	float Distance = FVector::Distance(Controller->GetPawn()->GetActorLocation(), TargetLocation);
	/** �ж� */
	if (Distance <= this->Distance)
	{
		return true;
	}

	return false;
}
