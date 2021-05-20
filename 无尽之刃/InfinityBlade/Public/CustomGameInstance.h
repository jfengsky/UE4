// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/LoadUserWidget.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "CustomGameInstance.generated.h"

/**
 * ��Ϸʵ��
 */
UCLASS()
class INFINITYBLADE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** �洢���ݼ��� */
	TMap<FString, FString> ContextMap;
	/** ���ص�UI */
	UPROPERTY()
		ULoadUserWidget* LoadWidget;

public:
	/** ��ʼ������ */
	virtual void Init() override;
	/** ��ͼ���ؿ�ʼ�ķ��� */
	UFUNCTION()
		void PreLoadMap(const FString& Map);
	/** ��ͼ���ؽ����ķ��� */
	UFUNCTION()
		void PostLoadMap(UWorld* World);
	/** �Ƿ������� */
	UFUNCTION(BlueprintCallable, Category = LoadFunction)
		bool GetLoadStatus();
};

