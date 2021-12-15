// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"

/*���췽��*/
AAICharacter::AAICharacter()
{
	/*��ʼ��UI���*/
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(GetMesh());
}

// ��Ϸ��ʼ���õķ���
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��ʼ��Ѫ��
	HPBar = Cast<UProgressBar>(WidgetComp->GetUserWidgetObject()->GetWidgetFromName(TEXT("ProgressBar_AIHP")));

	CurrentHPText = Cast<UTextBlock>(WidgetComp->GetUserWidgetObject()->GetWidgetFromName(TEXT("TextBlock_HP")));
	
	// ��ʼ����Ѫ��
	TotalHP = 100.f;

	// ��ʼ����ǰѪ��
	CurrentHP = 100.f;

	// ��ʼ��Ѫ��UI
	HPBar->SetPercent(CurrentHP/TotalHP);

	CurrentHPText->SetText(FText::FromString(FString::SanitizeFloat(CurrentHP)));
}

/*��д�ܵ��˺��ķ���*/
float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Blue, FString::SanitizeFloat(DamageAmount));

	if (DamageCauser == this)
	{
		return 0.f;
	}
	
	// ��ǰѪ������
	CurrentHP = CurrentHP - DamageAmount;
	// ����UI
	HPBar->SetPercent(CurrentHP/TotalHP);

	CurrentHPText->SetText(FText::FromString(FString::SanitizeFloat(CurrentHP)));

	if (CurrentHP <= 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage, 1.f);
	} else
	{
		// �������˶���
        GetMesh()->GetAnimInstance()->Montage_Play(DamageMontage, 1.f);
	}
	
	return  DamageAmount;
}

