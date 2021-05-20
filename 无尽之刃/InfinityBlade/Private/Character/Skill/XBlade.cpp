// Fill out your copyright notice in the Description page of Project Settings.

#include "XBlade.h"


/** ���췽�� */
AXBlade::AXBlade()
{
	/** ��ʼ��������� */
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	/** ���ø���� */
	SceneComponent->SetupAttachment(RootComponent);
	/** ��ʼ����������� */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** ���ø���� */
	CapsuleComponent->SetupAttachment(SceneComponent);
	/** ��ʼ��������Ч��� */
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	/** ���ø���� */
	ParticleSystemComponent->SetupAttachment(CapsuleComponent);
	/** ��������ʱ�� */
	InitialLifeSpan = 10.f;
}

/** ��Ϸ��ʼ���õķ��� */
void AXBlade::BeginPlay()
{
	Super::BeginPlay();
	
}

