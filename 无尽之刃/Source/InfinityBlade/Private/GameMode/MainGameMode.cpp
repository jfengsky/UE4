// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Character/XPlayerController.h"
#include "Character/XPlayerState.h"

/* ���췽�� */
AMainGameMode::AMainGameMode()
{
	/* �ҵ���Դ�����ͼ�� */
	ConstructorHelpers::FClassFinder<ACharacter> CharacterFinder(TEXT("/Game/Character/BP_XCharacter"));
	DefaultPawnClass = CharacterFinder.Class;

	/*���ÿ�����*/
	PlayerControllerClass = AXPlayerController::StaticClass();

	/*�������״̬*/
	PlayerStateClass = AXPlayerState::StaticClass();
}
