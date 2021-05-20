// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGameInstance.h"
#include <MoviePlayer.h>

/** ��ʼ������ */
void UCustomGameInstance::Init()
{
	UGameInstance::Init();

	/** ��ʼ���ص�ͼ��ί�� */
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::PreLoadMap);
	/** �������ص�ͼ��ί�� */
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UCustomGameInstance::PostLoadMap);
	/** ��ʼ�� */
	LoadWidget = CreateWidget<ULoadUserWidget>(this, LoadClass<ULoadUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoadWidget.BP_LoadWidget_C'")));
}

/** ��ͼ���ؿ�ʼ�ķ��� */
void UCustomGameInstance::PreLoadMap(const FString& Map)
{
	/** �ж��Ƿ��Ǽ��ص����ؿ� */
	if (Map.Equals("/Game/Map/Map_Main"))
	{
		/** ����һ����Ļ�������Զ��� */
		FLoadingScreenAttributes LoadingAttr;
		/** �ֶ��ĵ���������� */
		LoadingAttr.bWaitForManualStop = true;
		/** ���ü��ص�Widget */
		LoadingAttr.WidgetLoadingScreen = LoadWidget->TakeWidget();
		/** ���ü�����Ļ */
		GetMoviePlayer()->SetupLoadingScreen(LoadingAttr);
	}
}

/** ��ͼ���ؽ����ķ��� */
void UCustomGameInstance::PostLoadMap(UWorld* World)
{
	
}

/** �Ƿ������� */
bool UCustomGameInstance::GetLoadStatus()
{
	/** �����Ƿ��Ѿ�������� */
	return GetMoviePlayer()->IsLoadingFinished();
}
