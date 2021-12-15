// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartGameMode.generated.h"

/**
 * ��Ϸ��ʼ��ģʽ��
 */
UCLASS()
class INFINITYBLADE_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	/* ��ʼ���� */
	UPROPERTY()
		class UStartUserWidget* StartWidget;

	/* ��Ϸע����� */
	UPROPERTY()
		class URegisterUserWidget* RegisterWidget;

	UPROPERTY()
		class ULoginUserWidget* LoginWidget;

public:

	/* ��Ϸ��ʼ�͵��÷��� */
	virtual void BeginPlay() override;

	/* ע���˺Ű�ť����¼� */
	UFUNCTION()
		void RegisterBtnClickedEvent();

	/* ע��ҳ�淵�ذ�ť����¼� */
	UFUNCTION()
		void BackBtnOnClickedEvent();

	/* ��ʼ��Ϸ��ť����¼� */
	UFUNCTION()
		void StartBtnClickedEvent();

	/* ��¼ҳ�淵�ذ�ť����¼� */
	UFUNCTION()
		void LoginBackBtnOnClickedEvent();
};
