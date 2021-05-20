// Fill out your copyright notice in the Description page of Project Settings.

#include "StartGameMode.h"

/** ��Ϸ��ʼ���õķ��� */
void AStartGameMode::BeginPlay()
{
	/** ��ʼ����Ϸ��ʼ���� */
	StartWidget = CreateWidget<UStartUserWidget>(GetGameInstance(), LoadClass<UStartUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_StartUserWidget.BP_StartUserWidget_C'")));
	/** ��ӵ��ӿ� */
	StartWidget->AddToViewport();

	/** ��ʼ��Ϸ��ť�ĵ���¼� */
	StartWidget->StartBtn->OnClicked.AddDynamic(this, &AStartGameMode::StartBtnOnClickedEvent);
	/** ע���˺Ű�ť�ĵ���¼� */
	StartWidget->RegisterBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBtnOnClickedEvent);
	
	/** ��ʼ����Ϸ��¼���� */
	LoginWidget = CreateWidget<ULoginUserWidget>(GetGameInstance(), LoadClass<ULoginUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoginUserWidget.BP_LoginUserWidget_C'")));
	/** ���õ�¼���淵�ذ�ť�ĵ���¼� */
	LoginWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::LoginBackBtnOnClickedEvent);

	/** ��ʼ��ע���˺Ž��� */
	RegisterWidget = CreateWidget<URegisterUserWidget>(GetGameInstance(), LoadClass<URegisterUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_RegisterUserWidget.BP_RegisterUserWidget_C'")));
	/** ����ע����淵�ذ�ť�ĵ���¼� */
	RegisterWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBackBtnOnClickedEvent);
}

/** ��ʼ��Ϸ��ť����¼� */
void AStartGameMode::StartBtnOnClickedEvent()
{
	/** ��Ϸ��ʼ������ӿ����Ƴ� */
	StartWidget->RemoveFromViewport();
	/** ��¼��Ϸ������ӵ��ӿ� */
	LoginWidget->AddToViewport();
}

/** ע���˺Ű�ť����¼� */
void AStartGameMode::RegisterBtnOnClickedEvent()
{
	/** ��Ϸ��ʼ������ӿ����Ƴ� */
	StartWidget->RemoveFromViewport();
	/** ע���˺Ž�����ӵ��ӿ��� */
	RegisterWidget->AddToViewport();
}

/** ��¼ҳ�淵�ذ�ť����¼� */
void AStartGameMode::LoginBackBtnOnClickedEvent()
{
	/** ��¼�˺Ž�����ӿ����Ƴ� */
	LoginWidget->RemoveFromViewport();
	/** ��Ϸ��ʼ������ӵ��ӿڵ��� */
	StartWidget->AddToViewport();
}

/** ע��ҳ�淵�ذ�ť����¼� */
void AStartGameMode::RegisterBackBtnOnClickedEvent()
{
	/** ע���˺Ž�����ӿ����Ƴ� */
	RegisterWidget->RemoveFromViewport();
	/** ��Ϸ��ʼ������ӵ��ӿڵ��� */
	StartWidget->AddToViewport();
}
