// Fill out your copyright notice in the Description page of Project Settings.


#include "CiKeCharacter.h"
#include "Engine\SkeletalMesh.h"

ACiKeCharacter::ACiKeCharacter()
{
	CiKeSkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("CiKeSkeletalMesh"));

	// 加载资源
	CiKeSkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'"));

	// 设置模型
	GetMesh()->SetSkeletalMesh(CiKeSkeletalMesh);

	// 指定动画
	static ConstructorHelpers::FClassFinder<UAnimInstance> CiKeAnim(TEXT("AnimBlueprint'/Game/Assets/AnimBlueprint/CiKeAnim/CiKeAnimBlueprint.CiKeAnimBlueprint_C'"));
	if(CiKeAnim.Class)
	{
		GetMesh()->SetAnimInstanceClass(CiKeAnim.Class);
	}
}
