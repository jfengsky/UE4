// Fill out your copyright notice in the Description page of Project Settings.

#include "StartUserWidget.h"

/** �ؼ�������ɺ��ʼ������ */
bool UStartUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/** ��ʼ����Ϸ��ʼ��ť */
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	/** ��ʼ��ע���˺Ű�ť */
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));
	/** ��ʼ���˳���Ϸ��ť */
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));
	/** �˳���Ϸ��ť����¼� */
	QuitBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuitBtnOnClickedEvent);

	return true;
}

/** �˳���Ϸ��ť����¼� */
void UStartUserWidget::QuitBtnOnClickedEvent()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit);
}
