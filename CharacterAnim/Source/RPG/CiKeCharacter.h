// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "CiKeCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ACiKeCharacter : public ABasicCharacter
{
	GENERATED_BODY()

public:
	ACiKeCharacter();
	
private:
	USkeletalMesh* CiKeSkeletalMesh;
};
