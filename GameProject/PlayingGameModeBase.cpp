// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingGameModeBase.h"
#include "PlayingController.h"
#include "PlayingCharacter.h"

APlayingGameModeBase::APlayingGameModeBase()
{
	// ����Ĭ�Ͻ�ɫ��  �����ǽ����ͼ��ʱ��Ĭ�Ͽ��ƵĽ�ɫ
	DefaultPawnClass = APlayingCharacter::StaticClass();

	// ����Ĭ�Ͽ�������  �����ǽ����ͼ��ʱ��Ĭ�ϵĽ�ɫ������
	PlayerControllerClass = APlayerController::StaticClass();
}