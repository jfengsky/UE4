// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIAnimInstance.h"

#include "AI/MonsterAIController.h"

// 更新人物移动速度
void UAIAnimInstance::UpdateSpeed()
{
	if (TryGetPawnOwner() != nullptr)
	{
		Speed = TryGetPawnOwner()->GetVelocity().Size();
	}
}

/*开始播放蒙太奇动画通知*/
void UAIAnimInstance::AnimNotify_PlayStart(UAnimNotify* Notify)
{
	bIsPlaying = true;
}

/*结束播放蒙太奇动画通知*/
void UAIAnimInstance::AnimNotify_PlayEnd(UAnimNotify* Notify)
{
	bIsPlaying = false;
}

// 死亡动画通知
void UAIAnimInstance::AnimNotify_Death(UAnimNotify* Notify)
{
	AMonsterAIController* Controller = Cast<AMonsterAIController>(TryGetPawnOwner()->GetController());

	// 销毁武器
	Controller->AIWeapon->Destroy();

	// 销毁人物模型
	TryGetPawnOwner()->Destroy();
}
