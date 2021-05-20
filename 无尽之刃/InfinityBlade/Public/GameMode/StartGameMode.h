// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UI/StartUserWidget.h"
#include "UI/LoginUserWidget.h"
#include "UI/RegisterUserWidget.h"
#include "StartGameMode.generated.h"

/**
 * ��ʼ��Ϸģʽ��
 */
UCLASS()
class INFINITYBLADE_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/** ��Ϸ��ʼ���� */
	UPROPERTY()
		UStartUserWidget* StartWidget;
	/** ��Ϸ��¼���� */
	UPROPERTY()
		ULoginUserWidget* LoginWidget;
	/** ��Ϸע����� */
	UPROPERTY()
		URegisterUserWidget* RegisterWidget;

public:
	/** ��Ϸ��ʼ���õķ��� */
	virtual void BeginPlay() override;
	/** ��ʼ��Ϸ��ť����¼� */
	UFUNCTION()
		void StartBtnOnClickedEvent();
	/** ע���˺Ű�ť����¼� */
	UFUNCTION()
		void RegisterBtnOnClickedEvent();
	/** ��¼ҳ�淵�ذ�ť����¼� */
	UFUNCTION()
		void LoginBackBtnOnClickedEvent();
	/** ע��ҳ�淵�ذ�ť����¼� */
	UFUNCTION()
		void RegisterBackBtnOnClickedEvent();
};
