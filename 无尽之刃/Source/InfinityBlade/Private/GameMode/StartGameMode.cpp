// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/StartGameMode.h"
#include "UI/StartUserWidget.h"
#include "UI/RegisterUserWidget.h"
#include "Components/Button.h"
#include "UI/LoginUserWidget.h"

/* 游戏开始就调用方法 */
void AStartGameMode::BeginPlay()
{

	/* 初始化开始界面 */
	StartWidget = CreateWidget<UStartUserWidget>(GetGameInstance(), LoadClass<UStartUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_StartUserWidget.BP_StartUserWidget_C'")));

	/* 添加到屏幕 */
	StartWidget->AddToViewport();

	/* 开始游戏按钮绑定事件 */
	StartWidget->StartBtn->OnClicked.AddDynamic(this, &AStartGameMode::StartBtnClickedEvent);

	/* 注册账号按钮点击事件 */
	StartWidget->RegisterBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBtnClickedEvent);

	/* 初始化注册账号界面 */
	RegisterWidget = CreateWidget<URegisterUserWidget>(GetGameInstance(), LoadClass<URegisterUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_RegisterUserWidget.BP_RegisterUserWidget_C'")));

	/* 设置注册界面返回按钮点击事件 */
	RegisterWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::BackBtnOnClickedEvent);

	/* 初始化注册界面 */
	LoginWidget = CreateWidget<ULoginUserWidget>(GetGameInstance(), LoadClass<ULoginUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoginUserWidget.BP_LoginUserWidget_C'")));

	/* 登录页面返回按钮绑定点击事件 */
	LoginWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::LoginBackBtnOnClickedEvent);
}

/* 注册账号按钮点击事件 */
void AStartGameMode::RegisterBtnClickedEvent()
{
	/* 开始界面移除 */
	StartWidget->RemoveFromParent();

	/* 注册账号界面添加到视口 */
	RegisterWidget->AddToViewport();
}

/* 注册页面返回按钮点击事件 */
void AStartGameMode::BackBtnOnClickedEvent()
{
	/* 注册账号界面移除 */
	RegisterWidget->RemoveFromParent();

	/* 开始界面添加到视口 */
	StartWidget->AddToViewport();
}

/* 开始游戏按钮点击事件 */
void AStartGameMode::StartBtnClickedEvent()
{
	/* 开始界面移除 */
	StartWidget->RemoveFromParent();

	/* 登录界面添加到视口 */
	LoginWidget->AddToViewport();
}

/* 登录页面返回按钮点击事件 */
void AStartGameMode::LoginBackBtnOnClickedEvent()
{
	/* 登录界面移除 */
	LoginWidget->RemoveFromParent();

	/* 开始界面添加到视口 */
	StartWidget->AddToViewport();
}
