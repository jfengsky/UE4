// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

/**
 * 登录界面
 */
UCLASS()
class INFINITYBLADE_API ULoginUserWidget : public UUserWidget
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

	/* 登录按钮 */
	UPROPERTY()
		class UButton* LoginBtn;

	/* 提示框 */
	UPROPERTY()
		class UMessageUserWidget* MessageWidget;

public:
	/* 初始化登录界面 */
	virtual bool Initialize() override;

	/* 登录按钮点击事件 */
	UFUNCTION()
	void LoginBtnOnClickedEvent();

	/* 信息提示 */
	UFUNCTION()
	void MessageTip(FString msg);
};
