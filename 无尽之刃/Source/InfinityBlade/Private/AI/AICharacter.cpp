// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"

/*构造方法*/
AAICharacter::AAICharacter()
{
	/*初始化UI组件*/
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(GetMesh());
}

// 游戏开始调用的方法
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// 初始化血条
	HPBar = Cast<UProgressBar>(WidgetComp->GetUserWidgetObject()->GetWidgetFromName(TEXT("ProgressBar_AIHP")));

	CurrentHPText = Cast<UTextBlock>(WidgetComp->GetUserWidgetObject()->GetWidgetFromName(TEXT("TextBlock_HP")));
	
	// 初始化总血量
	TotalHP = 100.f;

	// 初始化当前血量
	CurrentHP = 100.f;

	// 初始化血量UI
	HPBar->SetPercent(CurrentHP/TotalHP);

	CurrentHPText->SetText(FText::FromString(FString::SanitizeFloat(CurrentHP)));
}

/*重写受到伤害的方法*/
float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Blue, FString::SanitizeFloat(DamageAmount));

	if (DamageCauser == this)
	{
		return 0.f;
	}
	
	// 当前血量减少
	CurrentHP = CurrentHP - DamageAmount;
	// 更新UI
	HPBar->SetPercent(CurrentHP/TotalHP);

	CurrentHPText->SetText(FText::FromString(FString::SanitizeFloat(CurrentHP)));

	if (CurrentHP <= 0)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage, 1.f);
	} else
	{
		// 播放受伤动画
        GetMesh()->GetAnimInstance()->Montage_Play(DamageMontage, 1.f);
	}
	
	return  DamageAmount;
}

