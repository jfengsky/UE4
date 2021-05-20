// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/CircularThrobber.h"
#include "UI/MessageUserWidget.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"
#include "LoginUserWidget.generated.h"

/**
 * ��¼����UI
 */
UCLASS()
class INFINITYBLADE_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** ���ذ�ť */
	UPROPERTY()
		UButton* BackBtn;
	/** �ǳ������ */
	UPROPERTY()
		UEditableTextBox* NicknameInput;
	/** ��������� */
	UPROPERTY()
		UEditableTextBox* PasswordInput;
	/** ��¼��ť */
	UPROPERTY()
		UButton* LoginBtn;

	/** ������ */
	UPROPERTY()
		UCircularThrobber* CircularThrobber;
	/** ��Ϣ��ʾ�� */
	UPROPERTY()
		UMessageUserWidget* MessageUserWidget;

public:
	/** �ؼ�������ɵĳ�ʼ������ */
	virtual bool Initialize() override;
	/** ��¼��ť����¼� */
	UFUNCTION()
		void LoginBtnOnClickedEvent();
	/** �û���¼�ķ��� */
	void AccountLoginFromServer(FString Nickname, FString Password);
	/** �������Ӧ���� */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);
};
