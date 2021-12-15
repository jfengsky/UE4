// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_DistanceTo.h"
#include "AI/AICharacter.h"
#include "AI/MonsterAIController.h"

// 重写判断的方法
bool UBTDecorator_DistanceTo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	// 获取Controller
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	// 获取黑板控件
	UBlackboardComponent* Blackboard = Controller->BlackboardComp;

	// 获取AI
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	
	// 获取目标位置
	FVector TargetLocation = Blackboard->GetValueAsVector(TEXT("TargetLocation"));

	// 获取两者距离
	float Dis = FVector::Distance(Controller->GetPawn()->GetActorLocation(), TargetLocation);

	if(Dis <= this->Distance)
	{
		return true;
	}
	
	return false;
}
