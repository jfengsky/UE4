// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 碰撞体
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;

	// 设置碰撞体大小
	OutCollision->SetBoxExtent(FVector(90.0f, 90.0f, 40.0f));

	// 启用物理
	OutCollision->SetSimulatePhysics(true);

	// OutCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	OutCollision->SetCollisionProfileName(TEXT("Pawn"));

	// 碰撞是水平的
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	// 设置空气阻力
	OutCollision->SetLinearDamping(2.0f);

	// 设置旋转阻力
	OutCollision->SetAngularDamping(0.5f);

	// 机身
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// TODO 设置机身相对碰撞盒子上下高度，这里实在蓝图里设置的，代码设置需要去学习
	// Mesh->SetRelativeLocation(FVector(100.0f,0.0f,0.0f));
	Mesh->SetupAttachment(OutCollision);

	// 四个旋翼
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	// 挂载到机身的插槽上
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);

	// 添加向上的力
	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	// 默认开启力
	UpThruster->SetAutoActivate(true);
	// TODO 力大小 代码设置一直不起作用，再去研究
	UpThruster->ThrustStrength = 980.0f;
	// 向上的力朝下推（类似火箭）
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));


	// 向前的力
	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector()));
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("%f"), GetInputAxisValue(TEXT("Lift")));
	// 当没有继续按向上按钮时，向上的力恢复默认，避免一直向上移动
	if (GetInputAxisValue(TEXT("Lift")) == 0.0f) {
		// UE_LOG(LogTemp, Warning, TEXT("stop"));
		UpThruster->ThrustStrength = 980.0f;
	}
	if (GetInputAxisValue(TEXT("Forward")) == 0.0f) {
		ForwardThruster->ThrustStrength = 0.0f;

		if (Mesh->GetRelativeRotation().Pitch != 0.0f) {
			float currentPitch = Mesh->GetRelativeRotation().Pitch;
			Mesh->AddRelativeRotation(FRotator(-currentPitch * DeltaTime, 0.0f, 0.0f));

			if (FMath::Abs(Mesh->GetRelativeRotation().Pitch)<= KINDA_SMALL_NUMBER) {
				Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
		}

	}


	RotatePaddle(DeltaTime);

}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);

}

void ADrone::Lift(float val)
{
	// 根据帧率修正
	UpThruster->ThrustStrength += val * LiftAcc * GetWorld()->DeltaTimeSeconds;
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftThrustMax, LiftThrustMax);
}

void ADrone::Forward(float val)
{
	ForwardThruster->ThrustStrength += val * ForwardAcc;
	ForwardThruster->ThrustStrength = FMath::Clamp(ForwardThruster->ThrustStrength, -ForwardThrustMax, ForwardThrustMax);
	
	float pitch = Mesh->GetRelativeRotation().Pitch;
	
	if (FMath::Abs(pitch) < 30.0f) {
		Mesh->AddRelativeRotation(FRotator(-50.0f * GetWorld()->DeltaTimeSeconds * val, 0.0f, 0.0f));
	}
}

void ADrone::Turn(float val)
{
	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector() * val * TurnStrength);
}

void ADrone::RotatePaddle(float Delta)
{
	for (auto paddle : Paddles) {
		paddle->AddRelativeRotation(FRotator(0.0f, Delta * PaddleRotateSpeed, 0.0f));
	}
}

