// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayingCharacter.generated.h"

UCLASS()
class GAMEPROJECT_API APlayingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 人物向前移动
	void MoveForward(float val);
	
	// 人物向后移动
	void MoveBack(float val);

	// 人物向左
	void MoveLeft(float val);

	// 人物向右
	void MoveRight(float val);

	// 跳跃开始
	void JumpStart();

	// 跳跃结束
	void JumpEnd();

	//这个是骨骼模型组件
	USkeletalMeshComponent* MeshComponent = nullptr;

	//这个是骨骼模型
	USkeletalMesh* SkeletalMesh = nullptr;

	//摄像机弹簧臂组件
	class USpringArmComponent* SpringArmComponent;

	//摄像机组件
	class UCameraComponent* CameraComponent;
};
