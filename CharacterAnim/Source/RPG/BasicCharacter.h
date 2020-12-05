// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UCLASS()
class RPG_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 摄像机手臂
	class USpringArmComponent* SpringArmComponent;

	// 摄像机
	class UCameraComponent* CameraComponent;

	// 碰撞体
	UCapsuleComponent* CapSuleComponent;

private:
	void MoveForword(float Val);
	void MoveBack(float Val);
	void MoveLeft(float Val);
	void MoveRight(float Val);
};
