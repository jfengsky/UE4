// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

UCLASS()
class TUTDRONE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	// 碰撞体
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* OutCollision;

	// 机身
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	// 四个旋翼
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle3;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle4;

	// 添加向上的力
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent* UpThruster;

	// 添加向前的力
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent* ForwardThruster;

	// 向上的力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Init")
	float LiftAcc = 1000.0f;

	// 向上力的范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float LiftThrustMax = 2000.0f;

	// 前进的力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardAcc = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardThrustMax = 2000.0f;

	// 旋转的力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float TurnStrength = 500000.0f;

	// 旋翼旋转速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float PaddleRotateSpeed = 2000.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void Lift(float val);

	UFUNCTION()
	void Forward(float val);

	UFUNCTION()
	void Turn(float val);

	// 旋翼数组
	TArray<UStaticMeshComponent*> Paddles;

	void RotatePaddle(float Delta);

};
