// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/XPlayerController.h"
#include "Character/XPlayerState.h"
#include "Character/XCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Pickup/ItemInfo.h"
#include "BagItemWidget.generated.h"

/**
 * 背包基本物品UI
 */
UCLASS()
class INFINITYBLADE_API UBagItemWidget : public UUserWidget
{
	GENERATED_BODY()

 public:

	UPROPERTY()
		AXCharacter* XCharacter;
	
	UPROPERTY()
		AXPlayerController* Controller;

	 UPROPERTY()
	 	AXPlayerState* PlayerState;
	
	 uint8 PickUpID;

	float Num;

	 EPickupInfoType InfoType;
	
	 UPROPERTY(Meta=(BindWidget))
	 	UTextBlock* Name;
	
	 UPROPERTY(Meta=(BindWidget))
	 	UImage* Pic;
	
	 UPROPERTY(Meta=(BindWidget))
	 	UTextBlock* Desc;
	
	 UPROPERTY()
	 	UButton* ItemUseBtn;

 public:
	 virtual bool Initialize() override;

	 // 使用按钮点击事件
	UFUNCTION()
	void UseBtnClickedEvent();
};
