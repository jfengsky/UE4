// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * ������
 */

UCLASS()
class INFINITYBLADE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	/*�������*/
	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComp;

	/*��ײ��*/
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;

	/*����ģ��*/
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponComp;

public:	
	// ���췽��
	AWeapon();

};
