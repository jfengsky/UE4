// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "RegisterUserWidget.generated.h"

/**
 * ��Ϸע�����
 */
UCLASS()
class INFINITYBLADE_API URegisterUserWidget : public UUserWidget
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

	/* ȷ����������� */
	UPROPERTY()
		class UEditableTextBox* RePasswordInput;

	/* ע���˺Ű�ť */
	UPROPERTY()
		class UButton* RegBtn;

	/* LoadingЧ�� */
	UPROPERTY()
		class UCircularThrobber* CircularThrobber;

	/* ��ʾ�� */
	UPROPERTY()
		class UMessageUserWidget* MessageWidget;

public:
	/* �����ʼ�� */
	virtual bool Initialize() override;

	/* ע���˺Ű�ť����¼� */
	UFUNCTION()
		void RegBtnOnClickedEvent();

	/*ע���˺ŷ���*/
	void AccountRegesterFromServer(FString& Nickname, FString& Password);

	/* ������Ӧ���� */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);

	/* ��Ϣ��ʾ */
	UFUNCTION()
		void MessageTip(FString msg);
};
