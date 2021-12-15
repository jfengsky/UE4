// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XBlade.generated.h"

/**
 * 无尽之刃技能
 */

UCLASS()
class INFINITYBLADE_API AXBlade : public AActor
{
	GENERATED_BODY()
	
public:	
	AXBlade();

public:
	
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneComp;
	
	// 粒子特效
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;

	// 碰撞体
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

protected:
	
	virtual void BeginPlay() override;

};
