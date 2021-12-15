// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFINITYBLADE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/*HP*/
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_HP;

	/*MP*/
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_MP;

	/* 普通攻击按钮 另一种事件绑定方式 按钮名必须与Widget里的保持一致*/
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button_Attack;

	// 寒冰之石技能
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_IceStone;

	// 冷却进度条
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* IceStoneCDBar;
	
	// 冷却时间
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* IceStoneCDText;

	// 恢复技能
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Cure;

	// 雷霆之光技能
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Thunder;

	// 无尽之刃技能
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_XBlade;

	// 人物基本信息按钮
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Package;
};
