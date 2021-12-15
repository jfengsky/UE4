// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/StartGameMode.h"
#include "UI/StartUserWidget.h"
#include "UI/RegisterUserWidget.h"
#include "Components/Button.h"
#include "UI/LoginUserWidget.h"

/* ��Ϸ��ʼ�͵��÷��� */
void AStartGameMode::BeginPlay()
{

	/* ��ʼ����ʼ���� */
	StartWidget = CreateWidget<UStartUserWidget>(GetGameInstance(), LoadClass<UStartUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_StartUserWidget.BP_StartUserWidget_C'")));

	/* ��ӵ���Ļ */
	StartWidget->AddToViewport();

	/* ��ʼ��Ϸ��ť���¼� */
	StartWidget->StartBtn->OnClicked.AddDynamic(this, &AStartGameMode::StartBtnClickedEvent);

	/* ע���˺Ű�ť����¼� */
	StartWidget->RegisterBtn->OnClicked.AddDynamic(this, &AStartGameMode::RegisterBtnClickedEvent);

	/* ��ʼ��ע���˺Ž��� */
	RegisterWidget = CreateWidget<URegisterUserWidget>(GetGameInstance(), LoadClass<URegisterUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_RegisterUserWidget.BP_RegisterUserWidget_C'")));

	/* ����ע����淵�ذ�ť����¼� */
	RegisterWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::BackBtnOnClickedEvent);

	/* ��ʼ��ע����� */
	LoginWidget = CreateWidget<ULoginUserWidget>(GetGameInstance(), LoadClass<ULoginUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoginUserWidget.BP_LoginUserWidget_C'")));

	/* ��¼ҳ�淵�ذ�ť�󶨵���¼� */
	LoginWidget->BackBtn->OnClicked.AddDynamic(this, &AStartGameMode::LoginBackBtnOnClickedEvent);
}

/* ע���˺Ű�ť����¼� */
void AStartGameMode::RegisterBtnClickedEvent()
{
	/* ��ʼ�����Ƴ� */
	StartWidget->RemoveFromParent();

	/* ע���˺Ž�����ӵ��ӿ� */
	RegisterWidget->AddToViewport();
}

/* ע��ҳ�淵�ذ�ť����¼� */
void AStartGameMode::BackBtnOnClickedEvent()
{
	/* ע���˺Ž����Ƴ� */
	RegisterWidget->RemoveFromParent();

	/* ��ʼ������ӵ��ӿ� */
	StartWidget->AddToViewport();
}

/* ��ʼ��Ϸ��ť����¼� */
void AStartGameMode::StartBtnClickedEvent()
{
	/* ��ʼ�����Ƴ� */
	StartWidget->RemoveFromParent();

	/* ��¼������ӵ��ӿ� */
	LoginWidget->AddToViewport();
}

/* ��¼ҳ�淵�ذ�ť����¼� */
void AStartGameMode::LoginBackBtnOnClickedEvent()
{
	/* ��¼�����Ƴ� */
	LoginWidget->RemoveFromParent();

	/* ��ʼ������ӵ��ӿ� */
	StartWidget->AddToViewport();
}
