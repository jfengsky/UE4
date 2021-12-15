// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "RegisterUserWidget.generated.h"

/**
 * 游戏注册界面
 */
UCLASS()
class INFINITYBLADE_API URegisterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/* 返回按钮 */
	UPROPERTY()
		class UButton* BackBtn;

	/* 昵称输入框 */
	UPROPERTY()
		class UEditableTextBox* NicknameInput;
	
	/* 密码输入框 */
	UPROPERTY()
		class UEditableTextBox* PasswordInput;

	/* 确认密码输入框 */
	UPROPERTY()
		class UEditableTextBox* RePasswordInput;

	/* 注册账号按钮 */
	UPROPERTY()
		class UButton* RegBtn;

	/* Loading效果 */
	UPROPERTY()
		class UCircularThrobber* CircularThrobber;

	/* 提示框 */
	UPROPERTY()
		class UMessageUserWidget* MessageWidget;

public:
	/* 组件初始化 */
	virtual bool Initialize() override;

	/* 注册账号按钮点击事件 */
	UFUNCTION()
		void RegBtnOnClickedEvent();

	/*注册账号方法*/
	void AccountRegesterFromServer(FString& Nickname, FString& Password);

	/* 请求响应方法 */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);

	/* 信息提示 */
	UFUNCTION()
		void MessageTip(FString msg);
};
