// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CharacterAnimInstance.h"

// Sets default values
APlayingCharacter::APlayingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	 //注册组件
	SkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkeletalMesh"));
	
	// 加载模型 
	SkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/TwinbladesAnimsetBase/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	
	GetMesh()->SetSkeletalMesh(SkeletalMesh);

	//设置模型位置,这里我们把人物以Z轴移动了90个单位，也就向下移动了90个单位
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	//设置模型面朝方向
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//注册摄像机手臂组件
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	//把这个组件绑定到根组件
	SpringArmComponent->SetupAttachment(RootComponent);

	//设置摄像机手臂和根组件之间的距离
	SpringArmComponent->TargetArmLength = 300.0f;

	//我们使用模型组件去进行旋转 如果不设置设个的话 Pitch轴无法进行视角移动
	SpringArmComponent->bUsePawnControlRotation = true;
	
	//注册摄像机组件
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//把摄像机绑定到摄像机手臂上
	CameraComponent->SetupAttachment(SpringArmComponent);

	//指认动画蓝图
	static ConstructorHelpers::FClassFinder<UCharacterAnimInstance> AnimInstance(TEXT("AnimBlueprint'/Game/TwinbladesAnimsetBase/UE4_Mannequin/Mesh/UE4_Mannequin_Skeleton_AnimBlueprint.UE4_Mannequin_Skeleton_AnimBlueprint_C'"));

	//判断资源是否存在
	if (AnimInstance.Succeeded()) {

		//赋值
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}
}

// Called when the game starts or when spawned
void APlayingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayingCharacter::MoveForward);
	InputComponent->BindAxis("MoveBack", this, &APlayingCharacter::MoveBack);
	InputComponent->BindAxis("MoveLeft", this, &APlayingCharacter::MoveLeft);
	InputComponent->BindAxis("MoveRight", this, &APlayingCharacter::MoveRight);


	// 视角，使用系统自带的
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// 跳跃
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayingCharacter::JumpStart);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayingCharacter::JumpEnd);
}

void APlayingCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val);
}

void APlayingCharacter::MoveBack(float val)
{
	AddMovementInput(-GetActorForwardVector(), val);
}

void APlayingCharacter::MoveLeft(float val)
{
	AddMovementInput(-GetActorRightVector(), val);
}

void APlayingCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val);
}

void APlayingCharacter::JumpStart()
{
	bPressedJump = true;
}

void APlayingCharacter::JumpEnd()
{
	bPressedJump = false;
}

