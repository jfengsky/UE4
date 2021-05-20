// Fill out your copyright notice in the Description page of Project Settings.

#include "MessageUserWidget.h"

/** �ؼ��������ʼ������ */
bool UMessageUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** ��ʼ���رհ�ť */
	CloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));
	/** ���ùرհ�ť�ĵ���¼� */
	CloseBtn->OnClicked.AddDynamic(this, &UMessageUserWidget::CloseBtnOnClickedEvent);
	/** ��ʾ��Ϣ���ʼ�� */
	MsgBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Msg")));

	return true;
}

/** �رհ�ť����¼� */
void UMessageUserWidget::CloseBtnOnClickedEvent()
{
	/** ���ص���Ϣ��ʾ�� */
	this->SetVisibility(ESlateVisibility::Hidden);
}
