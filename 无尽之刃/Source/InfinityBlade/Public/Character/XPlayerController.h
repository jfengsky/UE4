// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XPlayerState.h"
#include "XPlayerController.generated.h"

/**
 * ����Ӣ�۵Ŀ�����
 */
UCLASS()
class INFINITYBLADE_API AXPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/* ��ɫ���� */
	UPROPERTY()
	class AXCharacter* XCharacter;

	/*��ɫ״̬*/
	UPROPERTY()
		AXPlayerState* XPlayerState;

	/*Ӣ�۽�ɫ����ʵ��*/
	UPROPERTY()
	class UXAnimInstance* XAnimInstance;

	UPROPERTY()
	TArray<AActor*> AiArray;

	// ����֮ʯ������ȴ��ʱ��
	FTimerHandle IceStoneTimer;

	// ����֮ʯ���ܵ�ǰ��ȴʱ��
	float IceStoneCurrentCD;

	// ����֮ʯ�����ܹ���ȴʱ��
	float IceStoneTotalCD;
	
public:

	/*������UI*/
	UPROPERTY()
		class UMainUserWidget* MainWidget;

	/*��ʼ��������Ϣ����*/
	UPROPERTY()
	class UCharacterWidget *CharacterWidget;

	/*��������*/
	UPROPERTY()
		class AWeapon* XWeapon;

public:
	/* ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;

	/* ������ؼ� */
	virtual void SetupInputComponent() override;

	/*ǰ���ƶ�*/
	UFUNCTION()
		void MoveForward(float Speed);

	/*�����ƶ�*/
	UFUNCTION()
		void MoveRight(float Speed);

	/* �ؼ���ť��ʼ���¼����� */
	UFUNCTION()
		void InitWidgetEvent();

	/*������ť����¼�*/
	UFUNCTION()
		void AttackBtnOnClickedEvent();

	// �ͷź���֮ʯ����
	UFUNCTION()
		void IceStoneBtnOnClickedEvent();

	// ����֮ʯ��ȴ�ص�����
	void IceStoneCallback();

	// �ָ�����
	UFUNCTION()
		void CureBtnOnclickedEvent();

	// �ͷ�����֮�⼼��
	UFUNCTION()
		void ThunderBtnOnClickedEvent();

	// �ͷ��޾�֮�м���
	UFUNCTION()
		void XBladeBtnOnClickedEvent();
	
	/*��ʼ�����״̬*/
	UFUNCTION()
	void InitState();

	/*��ʼ��UI*/
	UFUNCTION()
	void InitUI();

	// �����˺�
	UFUNCTION()
		void WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// ��������
	UFUNCTION()
	void LockAI();

	// �����ɫ��Ϣ����¼�
	UFUNCTION()
		void CharacterBtnOnClickedEvent();
};
