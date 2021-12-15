// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XAnimInstance.h"

#include "Character/XCharacter.h"
#include "Character/XPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainUserWidget.h"

/*重写初始化方法*/
//void UXAnimInstance::NativeInitializeAnimation()
//{
//	Super::NativeInitializeAnimation();
//
//	/*获取Controller*/
//	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
//	
//	/*获取状态*/
//	XPlayState = XPlayerController->XPlayerState;
//
//	/*初始化基本攻击*/
//	NormalAttack = XPlayState->GetAttackDamage();
//}

/*开始播放蒙太奇动画通知*/
void UXAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/*结束播放蒙太奇动画通知*/
void UXAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/*开始计算攻击的动画通知*/
void UXAnimInstance::AnimNotify_AttackStart(UAnimNotify* Notify)
{
	bIsAttacking = true;
}

/*结束计算攻击的动画通知*/
void UXAnimInstance::AnimNotify_AttackEnd(UAnimNotify* Notify)
{
	bIsAttacking = false;
}

/*重置连击状态*/
void UXAnimInstance::AnimNotify_ResetSerialAttack(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = false;
	bIsEnableThreeAttack = false;
	bIsEnableFourAttack = false;
	bIsEnableFiveAttack = false;

	/* 重置连击伤害 */
	ResetNormalAttack();
}

/*进入第二次连击*/
void UXAnimInstance::AnimNotify_SecondAttackInput(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = true;

	/*伤害加成*/
	UpdateSerialAttack();
}

/*进入第三次连击*/
void UXAnimInstance::AnimNotify_ThreeAttackInput(UAnimNotify* Notify)
{
	bIsEnableThreeAttack = true;
	
	/*伤害加成*/
	UpdateSerialAttack();
}

/*进入第四次连击*/
void UXAnimInstance::AnimNotify_FourAttackInput(UAnimNotify* Notify)
{
	bIsEnableFourAttack = true;

	/*伤害加成*/
	UpdateSerialAttack();
}

/*进入第五次连击*/
void UXAnimInstance::AnimNotify_FiveAttackInput(UAnimNotify* Notify)
{
	bIsEnableFiveAttack = true;

	/*伤害加成*/
	UpdateSerialAttack();
}

// 寒冰之石技能产生通知
void UXAnimInstance::AnimNotify_SpawnIceStone(UAnimNotify* Notify)
{
	// 获取英雄角色
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());

	// 寒冰之石产生socket位置
	FVector SocketLocation = XCharacter->GetMesh()->GetSocketLocation(FName("IceStone"));

	// 获取socket的旋转
	FRotator SocketRotation = XCharacter->GetMesh()->GetSocketRotation(FName("IceStone"));
	
	// 生成寒冰之石
	AIceStone* IceStone = GetWorld()->SpawnActor<AIceStone>(XCharacter->IceStoneClass, SocketLocation, SocketRotation);
	
	// 发射寒冰之石
	IceStone->Shoot(SocketRotation.Vector());

	// 扣除魔法值
	MinusMP(10);

	// 更新UI
	UpDateMP();
}

// 恢复技能产生通知
void UXAnimInstance::AnimNotify_Cure(UAnimNotify* Notify)
{
	InitState();
	// 设置HP
	XPlayState->SetCurrentHP(XPlayState->GetCurrentHP() + 30.f);

	// 判断HP是否溢出
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	if (XPlayState->GetCurrentHP() > XCharacter->TotalHP)
	{
		XPlayState->SetCurrentHP(XCharacter->TotalHP);
	}
	
	// 更新HPUI
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	XPlayerController->MainWidget->ProgressBar_HP->SetPercent(XPlayState->GetCurrentHP()/XCharacter->TotalHP);

	// 扣除魔法
	MinusMP(10);
}

// 雷霆之光技能通知
void UXAnimInstance::AnimNotify_Thunder(UAnimNotify* Notify)
{
	InitState();

	// 获取英雄角色
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(XCharacter);
	// 产生伤害
	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), 50.f, 10.f, XCharacter->GetActorLocation(), 100.f, 300.f, .8f, nullptr, IgnoreActors, XCharacter, XPlayerController, ECC_Visibility);

	// 扣除魔法值
	MinusMP(20);

	// 更新UI
	UpDateMP();
}

// 无尽之刃技能通知
void UXAnimInstance::AnimNotify_XBlade(UAnimNotify* Notify)
{
	InitState();

	// 获取英雄角色
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());

	// 无尽之刃产生socket位置
	FVector SocketLocation = XCharacter->GetMesh()->GetSocketLocation(FName("IceStone"));
	
	// 生成无尽之刃
	AXBlade* XBlade = GetWorld()->SpawnActor<AXBlade>(XCharacter->XBladeClass, SocketLocation, FRotator(0,0,0));

	bIsPlayXBlade = true;

	// 设置定时器，10秒后状态正常
	XCharacter->GetWorldTimerManager().SetTimer(TimerHandle, this, &UXAnimInstance::TimerCallback, 10.f, false);
	
	/*武器绑定规则*/
	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	/* 绑定武器 */
	XBlade->AttachToComponent(XCharacter->GetMesh(), AttachmentRule, TEXT("XBlade_Socket"));
	
	// 技能伤害加成
	XPlayState->SetAttackDamage(XPlayState->GetAttackDamage() + 30.f);
	
	// 扣除魔法值
	MinusMP(50);

	// 更新UI
	UpDateMP();
}

// 无尽之刃技能结束,定时器回调
void UXAnimInstance::TimerCallback()
{
	bIsPlayXBlade = false;

	// 清除定时器
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	XCharacter->GetWorldTimerManager().ClearTimer(TimerHandle);
}

/*初始化玩家状态*/
void UXAnimInstance::InitState()
{
	if (XPlayState == nullptr) {
		/*获取Controller*/
		AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());

		/*获取状态*/
		XPlayState = XPlayerController->XPlayerState;

		/*初始化基本攻击*/
		NormalAttack = XPlayState->GetAttackDamage();
	}
}

/*重置为普通攻击*/
void UXAnimInstance::ResetNormalAttack()
{
	InitState();

	/*重置普通攻击伤害*/
	if(!bIsPlayXBlade)
	{
		XPlayState->SetAttackDamage(NormalAttack);
	}
	
	
}

/*连击加成伤害*/
void UXAnimInstance::UpdateSerialAttack()
{
	InitState();
	/*连击攻击伤害*/
	XPlayState->SetAttackDamage(XPlayState->GetAttackDamage() + 10.f);

}

// 扣除魔法值
void UXAnimInstance::MinusMP(float MP)
{
	InitState();
	XPlayState->SetCurrentMP(XPlayState->GetCurrentMP() - MP);
}

// 更新MPUI
void UXAnimInstance::UpDateMP()
{
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	XPlayerController->MainWidget->ProgressBar_MP->SetPercent(XPlayState->GetCurrentMP()/XCharacter->TotalMP);
}

/*更新人物移动速度*/
void UXAnimInstance::UpDateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}
