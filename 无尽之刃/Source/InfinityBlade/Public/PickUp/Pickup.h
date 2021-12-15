// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "PickUp/ItemInfo.h"
#include "Pickup.generated.h"

/*
 * 拾取的物品
 */

UCLASS()
class INFINITYBLADE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// 构造方法
	APickup();

public:
	// 碰撞胶囊体
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;

	// 网格模型组件 
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMeshComponent;

	// 物品信息
	UPROPERTY(EditAnywhere, Category="Property")
		FPickupInfo PickupInfo;
	
protected:
	// 游戏开始调用的方法
	virtual void BeginPlay() override;

public:
	// 物品碰撞方法
	UFUNCTION()
		void PickupOverlay(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
