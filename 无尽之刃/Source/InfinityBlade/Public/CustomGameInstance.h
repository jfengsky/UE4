// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * ��Ϸʵ��
 */
UCLASS()
class INFINITYBLADE_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/* �洢���ݵļ���*/
	TMap<FString, FString> ContextMap;

	/* ����UI */
	UPROPERTY()
		class ULoadUserWidget* LoadingWidget;
	
public:
	/*��ʼ������*/
	virtual void Init() override;

	/*��ͼ���ؿ�ʼ�ķ���*/
	UFUNCTION()
	void PreLoadMap(const FString& Map);

	/*�Ƿ�������*/
	UFUNCTION(BlueprintCallable, Category=LoadFunction)
		bool GetLoadStatus();

};
