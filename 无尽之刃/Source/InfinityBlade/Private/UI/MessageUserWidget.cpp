// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MessageUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

/* 控件创建后初始化方法 */
bool UMessageUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* 关闭按钮 */
	CloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	/* 关闭按钮绑定事件 */
	CloseBtn->OnClicked.AddDynamic(this, &UMessageUserWidget::CloseBtnClickedEvent);

	/* 信息提示 */
	MsgBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Message")));


	return true;
}

/* 关闭按钮点击事件 */
void UMessageUserWidget::CloseBtnClickedEvent()
{
	/* 隐藏信息提示框 */
	this->SetVisibility(ESlateVisibility::Hidden);
}
