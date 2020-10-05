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

	// ������ǰ�ƶ�
	void MoveForward(float val);
	
	// ��������ƶ�
	void MoveBack(float val);

	// ��������
	void MoveLeft(float val);

	// ��������
	void MoveRight(float val);

	// ��Ծ��ʼ
	void JumpStart();

	// ��Ծ����
	void JumpEnd();

	//����ǹ���ģ�����
	USkeletalMeshComponent* MeshComponent = nullptr;

	//����ǹ���ģ��
	USkeletalMesh* SkeletalMesh = nullptr;

	//��������ɱ����
	class USpringArmComponent* SpringArmComponent;

	//��������
	class UCameraComponent* CameraComponent;
};
