// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "StartUserWidget.generated.h"

/**
 * ��Ϸ��ʼ����
 */
UCLASS()
class INFINITYBLADE_API UStartUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/* ��ʼ��Ϸ��ť */
	UPROPERTY()
		class UButton* StartBtn;

	/* ע���˺Ű�ť */
	UPROPERTY()
		class UButton* RegisterBtn;

	/* �˳���Ϸ��ť */
	UPROPERTY()
		class UButton* QuitBtn;

	/* ���ٿ�ʼ��Ϸ��ť */
	UPROPERTY()
		class UButton* QuickStartBtn;

public:

	/* �ؼ�������ɺ��ʼ�� */
	virtual bool Initialize() override;

	/* �˳���Ϸ��ť����¼� */
	UFUNCTION()
		void QuitBtnClickedEvent();

	/* ���ű������� */
	UFUNCTION()
		void PlayBgm();

	// ���ٿ�ʼ��Ϸ��ť����¼�
	UFUNCTION()
		void QuickStartOnClickedEvent();

};
