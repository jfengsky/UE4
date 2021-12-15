// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StartUserWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"


/* �ؼ�������ɺ��ʼ�� */
bool UStartUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	/* ��ʼ����ʼ��Ϸ��ť */
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));

	/*��ʼ��ע���˺Ű�ť*/
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));

	/*��ʼ���˳���Ϸ��ť*/
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	/* �˳���Ϸ��ť���¼� */
	QuitBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuitBtnClickedEvent);

	/* ���ٿ�ʼ��Ϸ��ť */
	QuickStartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_QuickStart")));

	/* ���ٿ�ʼ��Ϸ */
	QuickStartBtn->OnClicked.AddDynamic(this, &UStartUserWidget::QuickStartOnClickedEvent);

	/* ���ű������� */
	PlayBgm();

	return true;
}

/* �˳���Ϸ��ť����¼� */
void UStartUserWidget::QuitBtnClickedEvent()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

/* ���ű������� */
void UStartUserWidget::PlayBgm()
{
	// ����Wave����
	auto cls = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("SoundWave'/Game/UI/Start/song16_master.song16_master'"));
	USoundWave* StartBGM = Cast<USoundWave>(cls);

	// ����Wave����
	UGameplayStatics::PlaySound2D(GetWorld(), StartBGM, 0.8f);
}

// ���ٿ�ʼ��Ϸ��ť����¼�
void UStartUserWidget::QuickStartOnClickedEvent()
{
	/* �л��ؿ�ǰ��һЩ���ݴ洢��GameInstance */
	UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());

	/* ����ϷID������ */
	GameInstance->ContextMap.Add("id", "10001");

	/* �л��ؿ�*/
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Map/Map_Main"));
}
