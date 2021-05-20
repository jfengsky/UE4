// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/CircularThrobber.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "UI/MessageUserWidget.h"
#include "RegisterUserWidget.generated.h"

/**
 * ��Ϸע�����UI
 */
UCLASS()
class INFINITYBLADE_API URegisterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** �����ϲ㰴ť */
	UPROPERTY()
		UButton* BackBtn;
	/** �ǳ������ */
	UPROPERTY()
		UEditableTextBox* NicknameInput;
	/** ��������� */
	UPROPERTY()
		UEditableTextBox* PasswordInput;
	/** ȷ����������� */
	UPROPERTY()
		UEditableTextBox* RePasswordInput;
	/** ע�ᰴť */
	UPROPERTY()
		UButton* RegisterBtn;

	/** ���ؿ� */
	UPROPERTY()
		UCircularThrobber* CircularThrobber;
	/** ��ʾ��UI */
	UPROPERTY()
		UMessageUserWidget* MessageUserWidget;

public:
	/** �ؼ�������ɺ��ʼ������ */
	virtual bool Initialize() override;
	/** ע���˺Ű�ť����¼� */
	UFUNCTION()
		void RegisterBtnOnClickedEvent();
	/** �˺�ע�᷽�� */
	void AccountRegisterFromServer(FString& Nickname, FString& Password);
	/** ������Ӧ���� */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);
};
