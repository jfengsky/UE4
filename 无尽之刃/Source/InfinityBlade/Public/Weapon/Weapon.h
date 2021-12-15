// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * 武器类
 */

UCLASS()
class INFINITYBLADE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	/*场景组件*/
	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComp;

	/*碰撞体*/
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;

	/*武器模型*/
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* WeaponComp;

public:	
	// 构造方法
	AWeapon();

};
