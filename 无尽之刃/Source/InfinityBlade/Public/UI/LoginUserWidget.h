// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

/**
 * ��¼����
 */
UCLASS()
class INFINITYBLADE_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/* ���ذ�ť */
	UPROPERTY()
		class UButton* BackBtn;

	/* �ǳ������ */
	UPROPERTY()
		class UEditableTextBox* NicknameInput;

	/* ��������� */
	UPROPERTY()
		class UEditableTextBox* PasswordInput;

	/* ��¼��ť */
	UPROPERTY()
		class UButton* LoginBtn;

	/* ��ʾ�� */
	UPROPERTY()
		class UMessageUserWidget* MessageWidget;

public:
	/* ��ʼ����¼���� */
	virtual bool Initialize() override;

	/* ��¼��ť����¼� */
	UFUNCTION()
	void LoginBtnOnClickedEvent();

	/* ��Ϣ��ʾ */
	UFUNCTION()
	void MessageTip(FString msg);
};
