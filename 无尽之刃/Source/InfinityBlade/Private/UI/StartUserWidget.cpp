// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StartUserWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"


/* 控件创建完成后初始化 */
bool UStartUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* 初始化开始游戏按钮 */
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));

	/*初始化注册账号按钮*/
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));

	/*初始化退出游戏按钮*/
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	/* 退出游戏按钮绑定事件 */
	QuitBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuitBtnClickedEvent);

	/* 快速开始游戏按钮 */
	QuickStartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_QuickStart")));

	/* 快速开始游戏 */
	QuickStartBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuickStartOnClickedEvent);

	/* 播放背景音乐 */
	PlayBgm();

	return true;
}

/* 退出游戏按钮点击事件 */
void UStartUserWidget::QuitBtnClickedEvent()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

/* 播放背景音乐 */
void UStartUserWidget::PlayBgm()
{
	// 加载Wave音乐
	auto cls = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("SoundWave'/Game/UI/Start/song16_master.song16_master'"));
	USoundWave* StartBGM = Cast<USoundWave>(cls);

	// 播放Wave音乐
	UGameplayStatics::PlaySound2D(GetWorld(), StartBGM, 0.8f);
}

// 快速开始游戏按钮点击事件
void UStartUserWidget::QuickStartOnClickedEvent()
{
	/* 切换关卡前把一些数据存储到GameInstance */
	UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());

	/* 把游戏ID存起来 */
	GameInstance->ContextMap.Add("id", "10001");

	/* 切换关卡*/
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Map_Main"));
}
