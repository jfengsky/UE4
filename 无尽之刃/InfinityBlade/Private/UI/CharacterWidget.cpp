// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWidget.h"

/** ��д��ť��ʼ������ */
bool UCharacterWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** ��ʼ���رհ�ť */
	BtnClose = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));
	/** �󶨵���¼� */
	BtnClose->OnClicked.AddDynamic(this, &UCharacterWidget::CloseBtnOnClickedEvent);
	/** ��ʼ���������� */
	ScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBoxBag")));

	return true;
}

/** �رհ�ť����¼� */
void UCharacterWidget::CloseBtnOnClickedEvent()
{
	this->RemoveFromViewport();
}
