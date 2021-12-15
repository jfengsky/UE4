// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/XBlade.h"
#include "Character/XPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

AXBlade::AXBlade()
{
	// 初始化场景组件
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComponent);
	
	// 初始化胶囊提碰撞组件
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));

	//设置为父组件
	CapsuleComp->SetupAttachment(SceneComp);
	
	// 初始化粒子特效组件
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));

	// 绑定到父组件上
	ParticleSystemComp->SetupAttachment(SceneComp);

	// 设置销毁时间
	InitialLifeSpan = 10.f;
}

void AXBlade::BeginPlay()
{
	Super::BeginPlay();
}



