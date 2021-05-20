// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

/** ���췽�� */
AWeapon::AWeapon()
{
	/** ��ʼ������ģ����� */
	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponComponent"));
	/** ��������ģ�͵ĸ���� */
	WeaponComponent->SetupAttachment(RootComponent);
	/** ��ʼ����ײ����� */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** ������ײ������ĸ���� */
	CapsuleComponent->SetupAttachment(WeaponComponent);
}