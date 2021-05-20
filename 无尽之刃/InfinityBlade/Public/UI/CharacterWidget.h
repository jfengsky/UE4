// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "CharacterWidget.generated.h"

/**
 * �����ɫ��Ϣ��UI
 */
UCLASS()
class INFINITYBLADE_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** �رհ�ť */
	UPROPERTY()
		UButton* BtnClose;
	/** ���������� */
	UPROPERTY()
		UScrollBox* ScrollBox;
public:
	/** ��д��ť��ʼ������ */
	virtual bool Initialize() override;
	/** �رհ�ť����¼� */
	UFUNCTION()
		void CloseBtnOnClickedEvent();
};
