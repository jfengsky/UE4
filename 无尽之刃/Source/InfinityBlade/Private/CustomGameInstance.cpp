// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "UI/LoadUserWidget.h"
#include "MoviePlayer/Public/MoviePlayer.h"

/*初始化方法*/
void UCustomGameInstance::Init()
{
	UGameInstance::Init();

	/* 加载UI */
	LoadingWidget = CreateWidget<ULoadUserWidget>(this, LoadClass<ULoadUserWidget>(this, TEXT("WidgetBlueprint'/Game/UI/BP_LoadUserWidget.BP_LoadUserWidget_C'")));


	/* 开始加载地图的委托 */
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::PreLoadMap);

}


/*地图加载开始的方法*/
void UCustomGameInstance::PreLoadMap(const FString& Map)
{
	/* 判断是否加载的主关卡 */
	if (Map.Equals("/Game/Map/Map_Main")) {

		/* 创建一个屏幕加载对象 */
		FLoadingScreenAttributes LoadingAttr;

		/*手动点击切换场景*/
		LoadingAttr.bWaitForManualStop = true;

		/* 设置加载的Widget */
		LoadingAttr.WidgetLoadingScreen = LoadingWidget->TakeWidget();

		/* 设置加载屏幕 */
		GetMoviePlayer()->SetupLoadingScreen(LoadingAttr);
	}
}

/*是否加载完成*/
bool UCustomGameInstance::GetLoadStatus()
{
	return GetMoviePlayer()->IsLoadingFinished();
}
