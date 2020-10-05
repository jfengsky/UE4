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

	 //ע�����
	SkeletalMesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkeletalMesh"));
	
	// ����ģ�� 
	SkeletalMesh = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/TwinbladesAnimsetBase/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	
	GetMesh()->SetSkeletalMesh(SkeletalMesh);

	//����ģ��λ��,�������ǰ�������Z���ƶ���90����λ��Ҳ�������ƶ���90����λ
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));

	//����ģ���泯����
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//ע��������ֱ����
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	//���������󶨵������
	SpringArmComponent->SetupAttachment(RootComponent);

	//����������ֱۺ͸����֮��ľ���
	SpringArmComponent->TargetArmLength = 300.0f;

	//����ʹ��ģ�����ȥ������ת �������������Ļ� Pitch���޷������ӽ��ƶ�
	SpringArmComponent->bUsePawnControlRotation = true;
	
	//ע����������
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//��������󶨵�������ֱ���
	CameraComponent->SetupAttachment(SpringArmComponent);

	//ָ�϶�����ͼ
	static ConstructorHelpers::FClassFinder<UCharacterAnimInstance> AnimInstance(TEXT("AnimBlueprint'/Game/TwinbladesAnimsetBase/UE4_Mannequin/Mesh/UE4_Mannequin_Skeleton_AnimBlueprint.UE4_Mannequin_Skeleton_AnimBlueprint_C'"));

	//�ж���Դ�Ƿ����
	if (AnimInstance.Succeeded()) {

		//��ֵ
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


	// �ӽǣ�ʹ��ϵͳ�Դ���
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// ��Ծ
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

