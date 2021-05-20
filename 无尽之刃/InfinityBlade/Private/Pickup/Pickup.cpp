// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Character/XCharacter.h"

/** ���췽�� */
APickup::APickup()
{
	/** ��ʼ��������� */
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	/** ��ʼ����������� */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::PickupOverlap);
	/** ��ʼ������ģ�� */
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	/** ���Ÿ���� */
	SceneComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetupAttachment(SceneComponent);
	MeshComponent->SetupAttachment(CapsuleComponent);
}

/** ��Ϸ��ʼ���õķ��� */
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

/** ��Ʒ��ײ���� */
void APickup::PickupOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	AXCharacter* Character = Cast<AXCharacter>(OtherActor);
	Character->PickupArray.Add(PickupInfo);
	Destroy();
}