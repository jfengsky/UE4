// Fill out your copyright notice in the Description page of Project Settings.


#include "FaShiCharacter.h"
#include "Engine\SkeletalMesh.h"

AFaShiCharacter::AFaShiCharacter()
{
	FaShiSkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("CiKeSkeletalMesh"));

	// 加载资源
	FaShiSkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'"));

	// 设置模型
	GetMesh()->SetSkeletalMesh(FaShiSkeletalMesh);

	// 指定动画
	static ConstructorHelpers::FClassFinder<UAnimInstance> FaShiAnim(TEXT("AnimBlueprint'/Game/Assets/AnimBlueprint/FaShiAnim/FaShiAnimBlueprint.FaShiAnimBlueprint_C'"));
	if(FaShiAnim.Class)
	{
		GetMesh()->SetAnimInstanceClass(FaShiAnim.Class);
	}
}
