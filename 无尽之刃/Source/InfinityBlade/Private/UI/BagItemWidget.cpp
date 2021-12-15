// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BagItemWidget.h"

#include "Character/XPlayerController.h"
#include "Kismet/GameplayStatics.h"

bool UBagItemWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	// 初始化使用按钮
	ItemUseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Use")));

	// 绑定点击事件
	ItemUseBtn->OnClicked.AddDynamic(this, &UBagItemWidget::UseBtnClickedEvent);
	
	return true;
}

// 使用按钮点击事件
void UBagItemWidget::UseBtnClickedEvent()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("UseBtnClickedEvent"));

	if (PlayerState == nullptr)
	{
		Controller = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		XCharacter = Cast<AXCharacter>(Controller->GetPawn());
		
		PlayerState = Controller->XPlayerState;

		switch(InfoType)
		{
			case EPickupInfoType::HP:
				PlayerState->SetCurrentHP(PlayerState->GetCurrentHP() + Num);
				Controller->InitUI();
				break;
			case EPickupInfoType::MP:
				break;
			default:
				break;
		}
		this->RemoveFromParent();

		for (int i = 0; i < XCharacter->PickupArray.Num(); i++)
		{
			FPickupInfo Info = XCharacter->PickupArray[i];
			if(Info.ID == PickUpID)
			{
				XCharacter->PickupArray.RemoveAt(i);
			}
		}
		
	}
}
