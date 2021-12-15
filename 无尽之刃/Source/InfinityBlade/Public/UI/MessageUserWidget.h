// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageUserWidget.generated.h"

/**
 * 信息提示
 */
UCLASS()
class INFINITYBLADE_API UMessageUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/* 关闭按钮 */
	UPROPERTY()
		class UButton* CloseBtn;

	/* 信息提示 */
	UPROPERTY()
		class UTextBlock* MsgBlock;

public:

	/* 控件创建后初始化方法 */
	virtual bool Initialize() override;

	/* 关闭按钮点击事件 */
	UFUNCTION()
		void CloseBtnClickedEvent();

};
