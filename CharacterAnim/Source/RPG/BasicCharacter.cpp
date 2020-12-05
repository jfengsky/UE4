// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
	// 初始化人物朝向，方向位置
 	GetMesh()->SetRelativeLocation(FVector(0,0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	// 初始化摄像机手臂
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 500.0f;

	SpringArmComponent->SetupAttachment(RootComponent);

	// 开启鼠标Y轴控制
	SpringArmComponent->bUsePawnControlRotation = true;

	// 初始化摄像机
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	// 设置摄像机视野
	CameraComponent->FieldOfView = 85.0f;

	CameraComponent->SetupAttachment(SpringArmComponent);

	// 初始化碰撞体
	CapSuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapSuleComponent"));
	CapSuleComponent->SetCapsuleSize(34.0f, 94.0f);

	CapSuleComponent->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = 700;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasicCharacter::MoveForword);
	PlayerInputComponent->BindAxis("MoveBack", this, &ABasicCharacter::MoveBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasicCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ABasicCharacter::MoveLeft);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ABasicCharacter::MoveForword(float Val)
{
	FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, Val);
}

void ABasicCharacter::MoveBack(float Val)
{
	FVector Back = -GetActorForwardVector();
	AddMovementInput(Back, Val);
}

void ABasicCharacter::MoveLeft(float Val)
{
	FVector Right = -GetActorRightVector();
	AddMovementInput(Right, Val);
}

void ABasicCharacter::MoveRight(float Val)
{
	FVector Left = GetActorRightVector();
	AddMovementInput(Left, Val);
}

