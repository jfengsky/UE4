// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"
#include  "BasicCharacter.h"

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// 对象转化
	ABasicCharacter* Ch = Cast<ABasicCharacter>(TryGetPawnOwner());

	if(Ch)
	{
		// // 如果转化成功

		// 判断角色是否有移动过
		FVector Length = Ch->GetVelocity();

		IsMove = Length.Size();

		FRotator Rotator = Ch->GetActorRotation();

		Direction = CalculateDirection(Length, Rotator);
		
	}
}
