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

	/* ��ͨ������ť ��һ���¼��󶨷�ʽ ��ť��������Widget��ı���һ��*/
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button_Attack;

	// ����֮ʯ����
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_IceStone;

	// ��ȴ������
	UPROPERTY(Meta = (BindWidget))
	class UProgressBar* IceStoneCDBar;
	
	// ��ȴʱ��
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* IceStoneCDText;

	// �ָ�����
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Cure;

	// ����֮�⼼��
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Thunder;

	// �޾�֮�м���
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_XBlade;

	// ���������Ϣ��ť
	UPROPERTY(Meta = (BindWidget))
	class UButton* Button_Package;
};
