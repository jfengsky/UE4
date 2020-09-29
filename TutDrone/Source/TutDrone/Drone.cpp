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

	// ��ײ��
	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	RootComponent = OutCollision;

	// ������ײ���С
	OutCollision->SetBoxExtent(FVector(90.0f, 90.0f, 40.0f));

	// ��������
	OutCollision->SetSimulatePhysics(true);

	// OutCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	OutCollision->SetCollisionProfileName(TEXT("Pawn"));

	// ��ײ��ˮƽ��
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	// ���ÿ�������
	OutCollision->SetLinearDamping(2.0f);

	// ������ת����
	OutCollision->SetAngularDamping(0.5f);

	// ����
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// TODO ���û��������ײ�������¸߶ȣ�����ʵ����ͼ�����õģ�����������Ҫȥѧϰ
	// Mesh->SetRelativeLocation(FVector(100.0f,0.0f,0.0f));
	Mesh->SetupAttachment(OutCollision);

	// �ĸ�����
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	// ���ص�����Ĳ����
	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);

	// ������ϵ���
	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent);
	// Ĭ�Ͽ�����
	UpThruster->SetAutoActivate(true);
	// TODO ����С ��������һֱ�������ã���ȥ�о�
	UpThruster->ThrustStrength = 980.0f;
	// ���ϵ��������ƣ����ƻ����
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector()));


	// ��ǰ����
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
	// ��û�м��������ϰ�ťʱ�����ϵ����ָ�Ĭ�ϣ�����һֱ�����ƶ�
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
	// ����֡������
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

