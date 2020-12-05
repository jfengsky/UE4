// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BasicCharacter.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UPROPERTY(BlueprintReadOnly)
	uint8 MoveSpeed;

protected:

	// 判断角色是否有移动
	UPROPERTY(BlueprintReadOnly)
	float IsMove;

	// 角色的方向
	UPROPERTY(BlueprintReadOnly)
	float Direction;
};
