// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadUserWidget.h"

/** �ؼ�������ɳ�ʼ������ */
bool ULoadUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/** ��ʼ�������� */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName(TEXT("CircularThrobber_Load")));
	/** ��ʼ�������ı� */
	LoadingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Load")));
	/** ��ʼ��������ť */
	NextText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Next")));

	return true;
}