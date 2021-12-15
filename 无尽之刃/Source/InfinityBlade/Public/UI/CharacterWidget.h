// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "CharacterWidget.generated.h"

/**
 * 人物角色信息UI
 */
UCLASS()
class INFINITYBLADE_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 关闭按钮
	UPROPERTY()
	class UButton* ButtonClose;

	// 背包滚动盒子
	UPROPERTY()
		UScrollBox* ScrollBox;

public:

	// 重写界面初始化方法
	virtual bool Initialize() override;

	// 关闭按钮事件
	UFUNCTION()
		void CloseBtnOnClickedEvent();
};
