// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** ���췽�� */
AMonsterController::AMonsterController()
{
	/** ��ʼ����Ϊ���ؼ� */
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	/** ��ʼ���ڰ�ؼ� */
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

/** ��д���Ƶķ��� */
void AMonsterController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	/** ��ʼ��AI�� */
	Monster = Cast<AAICharacter>(InPawn);
	/** ��ʼ������ʵ�� */
	AnimInstance = Cast<UAIAnimInstance>(Monster->GetMesh()->GetAnimInstance());

	/** �ж��������Ƿ���Ч */
	if (Monster->AIWeaponClass)
	{
		/** ����һ���������� */
		AIWeapon = GetWorld()->SpawnActor<AWeapon>(Monster->AIWeaponClass);
		/** �󶨹��� */
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		/** ������ */
		AIWeapon->AttachToComponent(Monster->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
		/** �������ص��¼� */
		AIWeapon->CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMonsterController::WeaponOverlapDamage);
	}

	/** �ж���Ϊ���ؼ� */
	if (Monster->BehaviorTree)
	{
		/** ��ʼ���ڰ� */
		BlackboardComponent->InitializeBlackboard(*((Monster->BehaviorTree->BlackboardAsset)));
		/** ������Ϊ�� */
		BehaviorTreeComponent->StartTree(*(Monster->BehaviorTree));
	}
}

/** �����ص��˺��¼� */
void AMonsterController::WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "AI Damage...");
	if (AnimInstance->bIsPlaying)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, this, Monster, nullptr);
	}
}
