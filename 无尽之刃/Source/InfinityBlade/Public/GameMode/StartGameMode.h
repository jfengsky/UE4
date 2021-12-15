// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartGameMode.generated.h"

/**
 * 游戏开始的模式类
 */
UCLASS()
class INFINITYBLADE_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	/* 开始界面 */
	UPROPERTY()
		class UStartUserWidget* StartWidget;

	/* 游戏注册界面 */
	UPROPERTY()
		class URegisterUserWidget* RegisterWidget;

	UPROPERTY()
		class ULoginUserWidget* LoginWidget;

public:

	/* 游戏开始就调用方法 */
	virtual void BeginPlay() override;

	/* 注册账号按钮点击事件 */
	UFUNCTION()
		void RegisterBtnClickedEvent();

	/* 注册页面返回按钮点击事件 */
	UFUNCTION()
		void BackBtnOnClickedEvent();

	/* 开始游戏按钮点击事件 */
	UFUNCTION()
		void StartBtnClickedEvent();

	/* 登录页面返回按钮点击事件 */
	UFUNCTION()
		void LoginBackBtnOnClickedEvent();
};
