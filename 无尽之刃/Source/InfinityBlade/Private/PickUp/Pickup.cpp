// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/Pickup.h"

#include "Character/XCharacter.h"

// 构造方法
APickup::APickup()
{
	
	// 初始化网格模型
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// 附件到跟组件上
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	// 初始化碰撞胶囊体
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	
	// 附加到网格模型上
	CapsuleComponent->SetupAttachment(StaticMeshComponent);

	// 碰撞体绑定事件
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::PickupOverlay);
}

// 游戏开始调用的方法
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// 物品碰撞方法
void APickup::PickupOverlay(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("PickupOverlay"));

	AXCharacter* XCharacter = Cast<AXCharacter>(Other);

	XCharacter->PickupArray.Add(PickupInfo);

	this->Destroy();
	
}

