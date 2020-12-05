// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGGameModeBase.h"
#include "CiKeCharacter.h"
#include "FaShiCharacter.h"
#include "SheShouCharacter.h"
#include "CharacterPlayerController.h"


ARPGGameModeBase::ARPGGameModeBase()
{

	// 设置默认操作模型
	DefaultPawnClass = ACiKeCharacter::StaticClass();

	PlayerControllerClass = ACharacterPlayerController::StaticClass();
	
}
