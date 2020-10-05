// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//判断人物有没有移动
	UPROPERTY(BlueprintReadOnly)
	float IsMove;

	//判断人物有没有跳跃
	UPROPERTY(BlueprintReadOnly)
	bool IsJump;
	
};
