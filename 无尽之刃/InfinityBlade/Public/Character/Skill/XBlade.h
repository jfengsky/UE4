// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "XBlade.generated.h"

/**
 * �޾�֮������
 */
UCLASS()
class INFINITYBLADE_API AXBlade : public AActor
{
	GENERATED_BODY()
	
public:
	/** ������� */
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;
	/** ������Ч */
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ParticleSystemComponent;
	/** ��ײ�� */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;

public:	
	/** ���췽�� */
	AXBlade();

protected:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;

};
