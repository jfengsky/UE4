// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterAIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// 构造方法
AMonsterAIController::AMonsterAIController()
{
	// 初始化行为树控件
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));

	// 初始化黑板控件
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

// 重写控制的方法
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// 强转为AI
	Monster = Cast<AAICharacter>(InPawn);

	AnimInstance = Cast<UAIAnimInstance>(Monster->GetMesh()->GetAnimInstance());

	/*判断武器类是否有效*/
	if (Monster->AIWeaponClass) {

		/*生成武器对象*/
		AIWeapon = GetWorld()->SpawnActor<AWeapon>(Monster->AIWeaponClass);

		/*武器绑定规则*/
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

		/* 绑定武器 */
		AIWeapon->AttachToComponent(Monster->GetMesh(), AttachmentRule, TEXT("hand_rSocket"));

		// 绑定武器重叠事件
		AIWeapon->CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AMonsterAIController::WeaponOverlapDamage);
	}

	// 判断行为树控件
	if(Monster->BehaviorTree)
	{
		// 初始化黑板
		BlackboardComp->InitializeBlackboard(*((Monster->BehaviorTree->BlackboardAsset)));

		// 启动行为树
		BehaviorTreeComp->StartTree(*(Monster->BehaviorTree));
	}
}

void AMonsterAIController::WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("monster weapon"));
	if(AnimInstance->bIsPlaying)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.f, this, Monster, nullptr);
	}
}
