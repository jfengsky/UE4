// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageUserWidget.generated.h"

/**
 * ��Ϣ��ʾ
 */
UCLASS()
class INFINITYBLADE_API UMessageUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/* �رհ�ť */
	UPROPERTY()
		class UButton* CloseBtn;

	/* ��Ϣ��ʾ */
	UPROPERTY()
		class UTextBlock* MsgBlock;

public:

	/* �ؼ��������ʼ������ */
	virtual bool Initialize() override;

	/* �رհ�ť����¼� */
	UFUNCTION()
		void CloseBtnClickedEvent();

};
