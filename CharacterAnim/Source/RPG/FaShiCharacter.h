// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "FaShiCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AFaShiCharacter : public ABasicCharacter
{
	GENERATED_BODY()
public:
	AFaShiCharacter();

private:
	USkeletalMesh* FaShiSkeletalMesh;
};
