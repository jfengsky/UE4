// Fill out your copyright notice in the Description page of Project Settings.

#include "IceStone.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** ���췽�� */
AIceStone::AIceStone()
{
	/** ��ʼ����������� */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** ����ײ�¼� */
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AIceStone::OnOverlap);
	/** ���ø���� */
	CapsuleComponent->SetupAttachment(RootComponent);
	/** ��ʼ��ϵͳ������� */
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	/** ���ø���� */
	ParticleSystemComponent->SetupAttachment(CapsuleComponent);
	/** ��ʼ���ӵ��ƶ���� */
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	/** �����ӵ��ƶ�������µ���� */
	ProjectileMovementComponent->SetUpdatedComponent(CapsuleComponent);
	/** �����ӵ��ƶ�������ٶ� */
	ProjectileMovementComponent->InitialSpeed = 600.f;
	/** ���ú���֮ʯ�������� */
	InitialLifeSpan = 2.f;
}

/** ��Ϸ��ʼ���õķ��� */
void AIceStone::BeginPlay()
{
	Super::BeginPlay();
	
}

/** ���䷽�� */
void AIceStone::Shoot(FVector Direction)
{
	/** �������ٶ� */
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

/** �����¼� */
void AIceStone::OnOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "IceStone...");
	if (OtherActor)
	{
		/** �Ի��е�AI�����˺� */
		UGameplayStatics::ApplyPointDamage(OtherActor, 50.f, HitResult.ImpactPoint, HitResult, nullptr, this, nullptr);
		/** ������ը������Ч */
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, OtherActor->GetActorLocation());
		/** ���ű�ը���� */
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, OtherActor->GetActorLocation());
		/** ��������ϵͳ */
		ParticleSystemComponent->SetVisibility(false);
	}
}
