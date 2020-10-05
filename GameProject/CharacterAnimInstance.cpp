// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "PlayingCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//TryGetPawnOwner() 返回的是一个Pawn类，它通过骨骼模型组件返回指认了它的角色，然后再把返回的Pawn转换成我们想要的角色
	APlayingCharacter* Character = Cast<APlayingCharacter>(TryGetPawnOwner());
	if (Character) {
		//GetVelocity() 返回的是角色的移动组件的速度,如果这个值大于0说明Character在移动,Size() 是获取向量的模
		IsMove = Character->GetVelocity().Size();

		//IsFalling()  如果角色当前正在下降就返回真
		IsJump = Character->GetCharacterMovement()->IsFalling();
	}
}