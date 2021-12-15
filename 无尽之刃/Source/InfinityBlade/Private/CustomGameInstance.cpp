// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "UI/LoadUserWidget.h"
#include "MoviePlayer/Public/MoviePlayer.h"

/*��ʼ������*/
void UCustomGameInstance::Init()
{
	UGameInstance::Init();

	/* ����UI */
	LoadingWidget = CreateWidget<ULoadUserWidget>(this, LoadClass<ULoadUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoadUserWidget.BP_LoadUserWidget_C'")));


	/* ��ʼ���ص�ͼ��ί�� */
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::PreLoadMap);

}


/*��ͼ���ؿ�ʼ�ķ���*/
void UCustomGameInstance::PreLoadMap(const FString& Map)
{
	/* �ж��Ƿ���ص����ؿ� */
	if (Map.Equals("/Game/Map/Map_Main")) {

		/* ����һ����Ļ���ض��� */
		FLoadingScreenAttributes LoadingAttr;

		/*�ֶ�����л�����*/
		LoadingAttr.bWaitForManualStop = true;

		/* ���ü��ص�Widget */
		LoadingAttr.WidgetLoadingScreen = LoadingWidget->TakeWidget();

		/* ���ü�����Ļ */
		GetMoviePlayer()->SetupLoadingScreen(LoadingAttr);
	}
}

/*�Ƿ�������*/
bool UCustomGameInstance::GetLoadStatus()
{
	return GetMoviePlayer()->IsLoadingFinished();
}
