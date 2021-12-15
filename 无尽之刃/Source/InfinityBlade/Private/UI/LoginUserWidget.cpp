// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoginUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "UI/MessageUserWidget.h"

/* ��ʼ����¼���� */
bool ULoginUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* ���ذ�ť */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));

	/* �ǳ������ */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));

	/* ��������� */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));

	/* ��¼��ť */
	LoginBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Login")));
	LoginBtn->OnClicked.AddDynamic(this, &ULoginUserWidget::LoginBtnOnClickedEvent);

	/* ��ʼ����Ϣ��ʾ�� */
	MessageWidget = Cast<UMessageUserWidget>(GetWidgetFromName(TEXT("BP_MessageUserWidget")));

	return true;
}

/* ��¼��ť����¼� */
void ULoginUserWidget::LoginBtnOnClickedEvent()
{

	/* ��ȡ�����˺ŵ�ֵ */
	FString Nickname = NicknameInput->GetText().ToString();

	/* ��ȡ��������� */
	FString Password = PasswordInput->GetText().ToString();

	if (Nickname.IsEmpty() || Password.IsEmpty())
	{
		MessageTip("nickname or password can't empty!");
		return;
	}
}

/* ��Ϣ��ʾ */
void ULoginUserWidget::MessageTip(FString msg)
{
	MessageWidget->SetVisibility(ESlateVisibility::Visible);
	MessageWidget->MsgBlock->SetText(FText::FromString(msg));
}
