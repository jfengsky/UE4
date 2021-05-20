// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pickup/ItemInfo.h"
#include "Pickup.generated.h"

/**
 * ʰȡ����Ʒ
 */

UCLASS()
class INFINITYBLADE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	/** ������� */
	UPROPERTY(VisibleAnywhere)
		USceneComponent * SceneComponent;
	/** ��ײ������ */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;
	/** ����ģ����� */
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComponent;
	/** ��Ʒ��Ϣ */
	UPROPERTY(EditAnywhere, Category = "Property")
		FPickupInfo PickupInfo;
public:	
	/** ���췽�� */
	APickup();
	/** ��Ʒ��ײ���� */
	UFUNCTION()
		void PickupOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);

protected:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;
};
