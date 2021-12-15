// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterWidget.h"
#include "Components/Button.h"

// 重写界面初始化方法
bool UCharacterWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	// 初始化关闭按钮
	ButtonClose = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	// 绑定按钮点击事件
	ButtonClose->OnClicked.AddDynamic(this, &UCharacterWidget::CloseBtnOnClickedEvent);

	// 初始化背包滚动盒子
	ScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBoxBag")));
	
	return true;
}

// 关闭按钮事件
void UCharacterWidget::CloseBtnOnClickedEvent()
{
	this->RemoveFromParent();
}
