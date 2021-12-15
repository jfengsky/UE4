// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// 构造方法
AWeapon::AWeapon()
{
	/*初始化武器模型组件*/
	WeaponComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComp"));

	/*武器设为跟组件*/
	WeaponComp->SetupAttachment(RootComponent);
	
	/*初始化碰撞体组件*/
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));

	/* 碰撞体绑定到武器上 */
	CapsuleComp->SetupAttachment(WeaponComp);

}

