// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Tick.h"
#include "AI/AICharacter.h"
#include "AI/MonsterAIController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// 重写心跳节点
void UBTService_Tick::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 获取Controller
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	// 获取黑板控件
	UBlackboardComponent* Blackboard = Controller->BlackboardComp;

	// 设置SelfLocation
	Blackboard->SetValueAsVector(TEXT("SelfLocation"), Controller->GetPawn()->GetActorLocation());

	// 获取AI角色
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());

	// 获取角色朝向
	FRotator Rotaten =  Monster->GetArrowComponent()->GetRelativeRotation();

	// 设置SelfDirection
	Blackboard->SetValueAsVector(TEXT("SelfRotaion"), Rotaten.Vector());
	
	// 获取主角位置
	FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	// 设置TargetLocation
	Blackboard->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
	
	
}
