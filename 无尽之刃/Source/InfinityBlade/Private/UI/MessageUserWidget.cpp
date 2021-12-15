// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MessageUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

/* �ؼ��������ʼ������ */
bool UMessageUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* �رհ�ť */
	CloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	/* �رհ�ť���¼� */
	CloseBtn->OnClicked.AddDynamic(this, &UMessageUserWidget::CloseBtnClickedEvent);

	/* ��Ϣ��ʾ */
	MsgBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Message")));


	return true;
}

/* �رհ�ť����¼� */
void UMessageUserWidget::CloseBtnClickedEvent()
{
	/* ������Ϣ��ʾ�� */
	this->SetVisibility(ESlateVisibility::Hidden);
}
