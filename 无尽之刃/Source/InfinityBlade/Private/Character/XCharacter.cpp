// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/XPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/MainUserWidget.h"

// 构造方法
AXCharacter::AXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	/*初始化玩家总血量*/
	TotalHP = 100.0f;

	/*初始化玩家总魔法量*/
	TotalMP = 100.0f;

	/*初始化普通攻击伤害*/
	NormalAttack = 10.f;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0,-90.f,0));
	

	/*设置角色移动朝向*/
	GetCharacterMovement()->bOrientRotationToMovement = true;

	/*设置角色控制器是否控制朝向*/
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	/* 初始化相机组件 */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent")); \
	CameraComponent->SetupAttachment(RootComponent);

	/*相机角色控制器控制朝向*/
	CameraComponent->bUsePawnControlRotation = false;

	CameraComponent->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));

	CameraComponent->SetRelativeRotation(FRotator(-45.f, 0, 0));

}

// 游戏开始调用方法
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// 受到伤害的方法
float AXCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	AXPlayerController* Control = Cast<AXPlayerController>(GetController());

	AXPlayerState* PlayState = Cast<AXPlayerState>(Control->XPlayerState);

	PlayState->SetCurrentHP(PlayState->GetCurrentHP() - DamageAmount);
	
	Control->InitUI();
	
	return DamageAmount;
}

// Called every frame
//void AXCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void AXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

