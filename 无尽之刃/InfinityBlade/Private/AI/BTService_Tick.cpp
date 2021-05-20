// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Tick.h"
#include "AI/MonsterController.h"
#include "AI/AICharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** ��д�����ڵ� */
void UBTService_Tick::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/** ��ȡController */
	AMonsterController* Controller = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	/** ��ȡ�ڰ�ؼ� */
	UBlackboardComponent* Blackboard = Controller->BlackboardComponent;

	/** ����SelfLocation */
	Blackboard->SetValueAsVector(TEXT("SelfLocation"), Controller->GetPawn()->GetActorLocation());
	/** ��ȡAI��ɫ */
	AAICharacter* Monster = Cast<AAICharacter>(Controller->GetPawn());
	/** ��ȡ���� */
	FRotator Rotation = Monster->GetMesh()->GetComponentRotation();
	/** ����SelfDirection */
	Blackboard->SetValueAsVector(TEXT("SelfDirection"), Rotation.Vector());

	/** ��ȡ����λ�� */
	FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	/** ����TargetLocation */
	Blackboard->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
}
