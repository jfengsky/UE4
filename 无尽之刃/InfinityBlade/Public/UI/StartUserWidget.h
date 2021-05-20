// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "StartUserWidget.generated.h"

/**
 * ��Ϸ��ʼ����
 */
UCLASS()
class INFINITYBLADE_API UStartUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** ��ʼ��Ϸ��ť */
	UPROPERTY()
		UButton* StartBtn;
	/** ע���˺Ű�ť */
	UPROPERTY()
		UButton* RegisterBtn;
	/** �˳���Ϸ��ť */
	UPROPERTY()
		UButton* QuitBtn;

public:
	/** �ؼ�������ɺ��ʼ������ */
	virtual bool Initialize() override;
	/** �˳���Ϸ��ť����¼� */
	UFUNCTION()
		void QuitBtnOnClickedEvent();
};
