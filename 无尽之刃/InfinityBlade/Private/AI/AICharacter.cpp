// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"

/** ���췽�� */
AAICharacter::AAICharacter()
{
	/** ��ʼ��UI�ؼ� */
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
}

/** ��Ϸ��ʼ���õķ��� */
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	/** ��ʼ��Ѫ�� */
	HPBar = Cast<UProgressBar>(WidgetComponent->GetUserWidgetObject()->GetWidgetFromName(TEXT("AIHPBar")));
	/** ��ʼ����ǰѪ�� */
	CurrentHP = TotalHP;
	/** ��ʼ����ǰ��Ѫ��UI */
	HPBar->SetPercent(CurrentHP / TotalHP);
}

/** ��д�յ��˺��ķ��� */
float AAICharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Damage = " + FString::SanitizeFloat(Damage));
	
	if (DamageCauser == this)
	{
		return 0.f;
	}
	
	/** ��ǰѪ������ */
	CurrentHP -= Damage;
	/** ����UI */
	HPBar->SetPercent(CurrentHP / TotalHP);
	/** �ж�Ѫ�� */
	if (CurrentHP <= 0)
	{
		/** ������������ */
		GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage, 1.f);
	}
	else
	{
		/** �������˶��� */
		GetMesh()->GetAnimInstance()->Montage_Play(DamageMontage, 1.f);
	}

	return Damage;
}
