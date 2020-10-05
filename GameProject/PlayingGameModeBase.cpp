// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingGameModeBase.h"
#include "PlayingController.h"
#include "PlayingCharacter.h"

APlayingGameModeBase::APlayingGameModeBase()
{
	// 设置默认角色类  是我们进入地图的时候默认控制的角色
	DefaultPawnClass = APlayingCharacter::StaticClass();

	// 设置默认控制器类  是我们进入地图的时候默认的角色控制器
	PlayerControllerClass = APlayerController::StaticClass();
}