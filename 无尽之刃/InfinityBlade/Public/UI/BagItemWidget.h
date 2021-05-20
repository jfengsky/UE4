// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/XPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Character/XPlayerController.h"
#include "Character/XCharacter.h"
#include "Pickup/ItemInfo.h"
#include "BagItemWidget.generated.h"

/**
 * ����Item��UI
 */
UCLASS()
class INFINITYBLADE_API UBagItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
		AXCharacter * Character;
	UPROPERTY()
		AXPlayerController * Controller;
	UPROPERTY()
		AXPlayerState* State;
	uint8 PickupId;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock * Name;
	EPickupInfoType InfoType;
	float Num;
	UPROPERTY(Meta = (BindWidget))
		UImage* Pic;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* Desc;
	UPROPERTY()
		UButton* UseBtn;

public:
	/** �ؼ�������ɺ��ʼ������ */
		virtual bool Initialize() override;
	/** ��ť����¼� */
	UFUNCTION()
		void UseBtnOnClickedEvent();

	
};
