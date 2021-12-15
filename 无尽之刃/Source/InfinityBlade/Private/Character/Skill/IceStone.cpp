// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/IceStone.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// 构造方法
AIceStone::AIceStone()
{
	// 初始化碰撞体组件
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));

	// 绑定碰撞事件
	CapsuleComp->OnComponentHit.AddDynamic(this, &AIceStone::OnHit);

	//设置父组件
	CapsuleComp->SetupAttachment(RootComponent);
	
	// 初始化粒子组件
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));

	// 设置父组件
	ParticleSystemComp->SetupAttachment(CapsuleComp);
	
	// 初始化子弹移动组件
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	// 设置子弹移动组件更新的组件
	ProjectileMovementComp->SetUpdatedComponent(RootComponent);

	// 设置子弹速度
	ProjectileMovementComp->InitialSpeed = 600.f;

	// 设置寒冰之石生命周期
	InitialLifeSpan = 2.0f;
}

// 游戏开始调用的方法
void AIceStone::BeginPlay()
{
	Super::BeginPlay();
	
}
// 发射方法
void AIceStone::Shoot(FVector Direction)
{
	// 发射后的速度
	ProjectileMovementComp->Velocity = Direction * ProjectileMovementComp->InitialSpeed;
}

// 击中方法
void AIceStone::OnHit(UPrimitiveComponent* HitComp, AActor* Other, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("ice stone .."));

	// 产生伤害
	UGameplayStatics::ApplyPointDamage(Other, 20, Hit.ImpactPoint, Hit, nullptr, this, nullptr);

	// 产生粒子爆炸效果
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, Hit.ImpactPoint);

	// 播放爆炸声音
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, Other->GetActorLocation());
	
	// 隐藏粒子
	ParticleSystemComp->SetVisibility(false);

	this->Destroy();
}

