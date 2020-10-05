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

	//�ж�������û���ƶ�
	UPROPERTY(BlueprintReadOnly)
	float IsMove;

	//�ж�������û����Ծ
	UPROPERTY(BlueprintReadOnly)
	bool IsJump;
	
};
