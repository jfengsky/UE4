// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "SheShouCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ASheShouCharacter : public ABasicCharacter
{
	GENERATED_BODY()

public:
	ASheShouCharacter();

private:
	USkeletalMesh* SheShouSkeletalMesh;
};
