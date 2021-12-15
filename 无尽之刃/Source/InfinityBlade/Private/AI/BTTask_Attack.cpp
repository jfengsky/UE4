// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"

#include "AI/AIAnimInstance.h"
#include "AI/AICharacter.h"
#include "AI/MonsterAIController.h"
#include "Kismet/GameplayStatics.h"

// 重写任务节点
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	// 获取Controller
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	// 获取黑板控件
	UBlackboardComponent* Blackboard = Controller->BlackboardComp;

	// 获取AI
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());

	// 获取动画实例
	UAIAnimInstance* AIAnimInstance = Cast<UAIAnimInstance>(Monster->GetMesh()->GetAnimInstance());

	// 判断当前是否正在播放动画蒙太奇
	if (!AIAnimInstance->bIsPlaying)
	{

		// 朝向玩家
		Controller->SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		
		// 获取随机数
		int MontageIndex =  FMath::RandRange(0, (Monster->AttackMontages.Num() - 1));

		//随机播放攻击蒙太奇动画
		AIAnimInstance->Montage_Play(Monster->AttackMontages[MontageIndex], 1.0f);
	}
	
	// 获取目标位置
	// FVector TargetLocation = Blackboard->GetValueAsVector(TEXT("TargetLocation"));

	// 获取两者距离
	// float Distance = FVector::Distance(Controller->GetPawn()->GetActorLocation(), TargetLocation);

	// if(Distance <= Dis)
 //     	{
 //     		Controller->MoveToLocation(TargetLocation);
 //     		
 //     
 //     		// 获取随机数
 //     		int MontageIndex =  FMath::RandRange(0, (Monster->AttackMontages.Num() - 1));
 //     		
 //     		//随机播放攻击蒙太奇动画
 //     		AIAnimInstance->Montage_Play(Monster->AttackMontages[MontageIndex], 1.0f);
 //     		
 //     		
 //     		return EBTNodeResult::Succeeded;
 //     	}
	return EBTNodeResult::Succeeded;
	// return EBTNodeResult::Failed;
}
