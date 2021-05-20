// Fill out your copyright notice in the Description page of Project Settings.

#include "XAnimInstance.h"
#include "Character/XPlayerController.h"
#include "Character/XCharacter.h"
#include "Character/Skill/IceStone.h"
#include "Character/Skill/XBlade.h"

/** ���������ƶ��ٶ� */
void UXAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner()!=nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/** ��ʼ������̫�� */
void UXAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/** ����������̫�� */
void UXAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

/** ��ʼ������̫�� */
void UXAnimInstance::AnimNotify_AttackStart(UAnimNotify* Notify)
{
	bIsAttacking = true;
}

/** ����������̫�� */
void UXAnimInstance::AnimNotify_AttackEnd(UAnimNotify* Notify)
{
	bIsAttacking = false;
}

/** ��������״̬ */
void UXAnimInstance::AnimNotify_ResetSerialAttack(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = false;
	bIsEnableThreeAttack = false;
	bIsEnableFourAttack = false;
	bIsEnableFiveAttack = false;
	/** ���������˺� */
	ResetNormalAttack();
}

/** ����ڶ������� */
void UXAnimInstance::AnimNotify_SecondAttackInput(UAnimNotify* Notify)
{
	bIsEnableSecondAttack = true;
	/** �ӳ��˺��˺� */
	UpdateSerialAttack();
}

/** ������������� */
void UXAnimInstance::AnimNotify_ThreeAttackInput(UAnimNotify* Notify)
{
	bIsEnableThreeAttack = true;
	/** �ӳ��˺��˺� */
	UpdateSerialAttack();
}

/** ������Ĵ����� */
void UXAnimInstance::AnimNotify_FourAttackInput(UAnimNotify* Notify)
{
	bIsEnableFourAttack = true;
	/** �ӳ��˺��˺� */
	UpdateSerialAttack();
}

/** ������������ */
void UXAnimInstance::AnimNotify_FiveAttackInput(UAnimNotify* Notify)
{
	bIsEnableFiveAttack = true;
	/** �ӳ��˺��˺� */
	UpdateSerialAttack();
}

/** ��ʼ�����״̬ */
void UXAnimInstance::InitState()
{
	if (XPlayerState == nullptr)
	{
		/** ��ȡController */
		AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
		/** ��ȡ״̬ */
		XPlayerState = XPlayerController->XPlayerState;
		/** ��ʼ���������� */
		NormalAttack = XPlayerState->GetAttackDamage();
	}
}

/** ����Ϊ��ͨ���� */
void UXAnimInstance::ResetNormalAttack()
{
	/** ��ʼ�� */
	InitState();
	/** �����չ����˺� */
	if (!bIsXBlade)
	{
		XPlayerState->SetAttackDamage(NormalAttack);
	}
}

/** ���мӳ��˺� */
void UXAnimInstance::UpdateSerialAttack()
{
	/** ��ʼ�� */
	InitState();
	/** �ӳ��˺� */
	if (!bIsXBlade)
	{
		XPlayerState->SetAttackDamage(XPlayerState->GetAttackDamage() + 10.f);
	}
}

/** �۳�ħ��ֵ */
void UXAnimInstance::MinusMP(float MP)
{
	/** ��ʼ�� */
	InitState();
	/** �۳�ħ��ֵ */
	XPlayerState->SetCurrentMP(XPlayerState->GetCurrentMP() - MP);
	/** ֪ͨUI */
	UpdateMPUI();
}

/** ����MP��UI */
void UXAnimInstance::UpdateMPUI()
{
	/** ��ȡController */
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	/** ��ȡ��ɫ */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** ����MP��UI */
	XPlayerController->MainWidget->ProgressBar_MP->SetPercent(1.f - (XPlayerState->GetCurrentMP() / XCharacter->TotalMP));
}

/** ����֮ʯ����֪ͨ */
void UXAnimInstance::AnimNotify_SpawnIceStone(UAnimNotify* Notify)
{
	/** ��ȡӢ�۽�ɫ */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** ��ȡSocketλ�� */
	FVector Location = XCharacter->GetMesh()->GetSocketLocation(TEXT("IceStone"));
	/** ��ȡSocket����ת */
	FRotator Rotation = XCharacter->GetMesh()->GetSocketRotation(TEXT("IceStone"));
	/** ��������֮ʯ */
	AIceStone* IceStone = GetWorld()->SpawnActor<AIceStone>(XCharacter->IceStoneClass, Location, Rotation);
	/** �������֮ʯ */
	IceStone->Shoot(Rotation.Vector());
	/** �۳�ħ��ֵ */
	MinusMP(10.f);
}

/** �ָ�֮������֪ͨ */
void UXAnimInstance::AnimNotify_UseCure(UAnimNotify* Notify)
{
	/** ��ȡӢ�۽�ɫ */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** ��ʼ��״̬ */
	InitState();
	/** ���õ�ǰ��HP */
	XPlayerState->SetCurrentHP(XPlayerState->GetCurrentHP() + 30.f);
	/** �ж�HP�Ƿ���� */
	if (XPlayerState->GetCurrentHP() > XCharacter->TotalHP)
	{
		XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	}
	/** ��ȡController */
	AXPlayerController* XPlayerController = Cast<AXPlayerController>(TryGetPawnOwner()->GetController());
	/** ����HP��UI */
	XPlayerController->MainWidget->ProgressBar_HP->SetPercent(1.f - (XPlayerState->GetCurrentHP() / XCharacter->TotalHP));
	/** �۳�ħ��ֵ */
	MinusMP(10.f);
}

/** ����֮�����֪ͨ */
void UXAnimInstance::AnimNotify_UseThunder(UAnimNotify* Notify)
{
	/** ��ʼ��״̬ */
	InitState();
	/** �۳�ħ��ֵ */
	MinusMP(10.f);
	/** �����˺� */
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(TryGetPawnOwner());
	UGameplayStatics::ApplyRadialDamage(GetWorld(), 50.f, TryGetPawnOwner()->GetActorLocation(), 500.f, nullptr, IgnoreActors, TryGetPawnOwner(), TryGetPawnOwner()->GetController(), true, ECC_Visibility);
}

/** �޾�֮�в���֪ͨ */
void UXAnimInstance::AnimNotify_SpawnXBlade(UAnimNotify* Notify)
{
	/** ��ȡӢ�۽�ɫ */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** �����޾�֮�� */
	AXBlade* XBlade = GetWorld()->SpawnActor<AXBlade>(XCharacter->XBladeClass);
	/** �󶨹��� */
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	/** ���޾�֮�� */
	XBlade->AttachToComponent(XCharacter->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
	/** �۳�ħ��ֵ */
	MinusMP(50.f);
	/** ��ʼ�� */
	InitState();
	/** �ӳ��˺� */
	XPlayerState->SetAttackDamage(XPlayerState->GetAttackDamage() + 100.f);
	/** ����Ϊ�޾�֮��״̬ */
	bIsXBlade = true;
	/** ������ʱ�� */
	XCharacter->GetWorldTimerManager().SetTimer(TimerHandle, this, &UXAnimInstance::TimerCallback, 10.f, false);
}

/** ��ʱ���ص����� */
void UXAnimInstance::TimerCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Timer...");
	/** ����Ϊ�޾�֮��״̬ */
	bIsXBlade = false;
	/** ��ȡӢ�۽�ɫ */
	AXCharacter* XCharacter = Cast<AXCharacter>(TryGetPawnOwner());
	/** �����ʱ�� */
	XCharacter->GetWorldTimerManager().ClearTimer(TimerHandle);
}
