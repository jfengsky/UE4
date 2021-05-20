// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"
#include "LoadUserWidget.generated.h"

/**
 * ����UI
 */
UCLASS()
class INFINITYBLADE_API ULoadUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** ���ؽ����� */
	UPROPERTY()
		UCircularThrobber* CircularThrobber;
	/** �����ı� */
	UPROPERTY()
		UTextBlock* LoadingText;
	/** ������ť */
	UPROPERTY()
		UTextBlock* NextText;
public:
	/** �ؼ�������ɳ�ʼ������ */
	virtual bool Initialize() override;
};
