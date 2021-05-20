// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.generated.h"

/**
 * ������UI
 */
UCLASS()
class INFINITYBLADE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** HP */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
	/** HP */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_MP;
	/** ������ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Attack;

	/** ����֮ʯ���ܰ�ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_IceStone;
	/** ����֮ʯ������ȴ������ */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* IceStoneCDBar;
	/** ����֮ʯ������ȴʱ����ʾ */
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* IceStoneCDText;

	/** �ָ�֮�����ܰ�ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Cure;
	/** ����֮�⼼�ܰ�ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Thunder;
	/** �޾�֮�м��ܰ�ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_XBlade;

	/** ��ʾ�ı� */
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* MsgText;

	/** �����ɫ��Ϣ��ť */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Package;
	
};
