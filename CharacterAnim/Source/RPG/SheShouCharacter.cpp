// Fill out your copyright notice in the Description page of Project Settings.


#include "SheShouCharacter.h"
#include "Engine\SkeletalMesh.h"

ASheShouCharacter::ASheShouCharacter()
{
	
	SheShouSkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("CiKeSkeletalMesh"));

	// 加载资源
	SheShouSkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast.TwinBlast'"));

	// 设置模型
	GetMesh()->SetSkeletalMesh(SheShouSkeletalMesh);

	// 指定动画
	static ConstructorHelpers::FClassFinder<UAnimInstance> SheShouAnim(TEXT("AnimBlueprint'/Game/Assets/AnimBlueprint/SheShouAnim/SheShouBlueprint.SheShouBlueprint_C'"));
	if(SheShouAnim.Class)
	{
		GetMesh()->SetAnimInstanceClass(SheShouAnim.Class);
	}
}
