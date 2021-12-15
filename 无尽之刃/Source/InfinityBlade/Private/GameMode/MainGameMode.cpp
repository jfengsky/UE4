// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Character/XPlayerController.h"
#include "Character/XPlayerState.h"

/* 构造方法 */
AMainGameMode::AMainGameMode()
{
	/* 找到资源里的蓝图类 */
	ConstructorHelpers::FClassFinder<ACharacter> CharacterFinder(TEXT("/Game/Character/BP_XCharacter"));
	DefaultPawnClass = CharacterFinder.Class;

	/*设置控制器*/
	PlayerControllerClass = AXPlayerController::StaticClass();

	/*设置玩家状态*/
	PlayerStateClass = AXPlayerState::StaticClass();
}
