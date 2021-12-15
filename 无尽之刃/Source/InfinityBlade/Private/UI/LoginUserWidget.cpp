// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoginUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "UI/MessageUserWidget.h"

/* 初始化登录界面 */
bool ULoginUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* 返回按钮 */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));

	/* 昵称输入框 */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));

	/* 密码输入框 */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));

	/* 登录按钮 */
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Login")));
	LoginBtn->OnClicked.AddDynamic(this, &ULoginUserWidget::LoginBtnOnClickedEvent);

	/* 初始化信息提示框 */
	MessageWidget = Cast<UMessageUserWidget>(GetWidgetFromName(TEXT("BP_MessageUserWidget")));

	return true;
}

/* 登录按钮点击事件 */
void ULoginUserWidget::LoginBtnOnClickedEvent()
{

	/* 获取输入账号的值 */
	FString Nickname = NicknameInput->GetText().ToString();

	/* 获取输入的密码 */
	FString Password = PasswordInput->GetText().ToString();

	if (Nickname.IsEmpty() || Password.IsEmpty())
	{
		MessageTip("nickname or password can't empty!");
		return;
	}
}

/* 信息提示 */
void ULoginUserWidget::MessageTip(FString msg)
{
	MessageWidget->SetVisibility(ESlateVisibility::Visible);
	MessageWidget->MsgBlock->SetText(FText::FromString(msg));
}
