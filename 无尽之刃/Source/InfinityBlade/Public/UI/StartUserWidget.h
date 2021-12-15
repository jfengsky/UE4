// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "StartUserWidget.generated.h"

/**
 * 游戏开始界面
 */
UCLASS()
class INFINITYBLADE_API UStartUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/* 开始游戏按钮 */
	UPROPERTY()
		class UButton* StartBtn;

	/* 注册账号按钮 */
	UPROPERTY()
		class UButton* RegisterBtn;

	/* 退出游戏按钮 */
	UPROPERTY()
		class UButton* QuitBtn;

	/* 快速开始游戏按钮 */
	UPROPERTY()
		class UButton* QuickStartBtn;

public:

	/* 控件创建完成后初始化 */
	virtual bool Initialize() override;

	/* 退出游戏按钮点击事件 */
	UFUNCTION()
		void QuitBtnClickedEvent();

	/* 播放背景音乐 */
	UFUNCTION()
		void PlayBgm();

	// 快速开始游戏按钮点击事件
	UFUNCTION()
		void QuickStartOnClickedEvent();

};
