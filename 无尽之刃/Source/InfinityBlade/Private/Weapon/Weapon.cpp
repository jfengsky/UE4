// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// ���췽��
AWeapon::AWeapon()
{
	/*��ʼ������ģ�����*/
	WeaponComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComp"));

	/*������Ϊ�����*/
	WeaponComp->SetupAttachment(RootComponent);
	
	/*��ʼ����ײ�����*/
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));

	/* ��ײ��󶨵������� */
	CapsuleComp->SetupAttachment(WeaponComp);

}

