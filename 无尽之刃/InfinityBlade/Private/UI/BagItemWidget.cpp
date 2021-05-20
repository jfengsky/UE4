// Fill out your copyright notice in the Description page of Project Settings.

#include "BagItemWidget.h"

/** �ؼ�������ɺ��ʼ������ */
bool UBagItemWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** ��ʼ��ʹ�ð�ť */
	UseBtn = Cast<UButton>(GetWidgetFromName(TEXT("BtnUse")));
	/** �󶨵���¼� */
	UseBtn->OnClicked.AddDynamic(this, &UBagItemWidget::UseBtnOnClickedEvent);

	return true;
}

/** ��ť����¼� */
void UBagItemWidget::UseBtnOnClickedEvent()
{
	if (State == nullptr)
	{
		Controller = Cast<AXPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Character = Cast<AXCharacter>(Controller->GetPawn());
		State = Controller->XPlayerState;
	}

	switch (InfoType)
	{
	case EPickupInfoType::HP:
		State->SetCurrentHP(State->GetCurrentHP() + Num);
		Controller->UpdateUI();
		break;
	case EPickupInfoType::MP:
		break;
	default:
		break;
	}

	for (int i = 0; i < Character->PickupArray.Num(); i++)
	{
		FPickupInfo Info = Character->PickupArray[i];
		if (Info.ID == PickupId)
		{
			Character->PickupArray.RemoveAt(i);
		}
	}

	this->RemoveFromParent();
}
