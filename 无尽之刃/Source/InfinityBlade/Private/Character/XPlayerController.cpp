// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XPlayerController.h"

#include "AI/AICharacter.h"
#include "Character/XCharacter.h"
#include "UI/MainUserWidget.h"
#include "UI/CharacterWidget.h"
#include "Character/XAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/BagItemWidget.h"

/* ��Ϸ��ʼ���õķ��� */
void AXPlayerController::BeginPlay()
{
	/*��ʾ���ָ��*/
	bShowMouseCursor = true;

	/*��ʼ����ɫ����*/
	XCharacter = Cast<AXCharacter>(GetPawn());

	/*��ʼ������ʵ��*/
	XAnimInstance = Cast<UXAnimInstance>(XCharacter->GetMesh()->GetAnimInstance());

	/*��ʼ��������*/
	MainWidget = CreateWidget<UMainUserWidget>(GetGameInstance(), LoadClass<UMainUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_MainUserWidget.BP_MainUserWidget_C'")));

	/*��ʼ��������Ϣ����*/
	CharacterWidget = CreateWidget<UCharacterWidget>(GetGameInstance(), LoadClass<UCharacterWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_CharacterWidget.BP_CharacterWidget_C'")));
	
	/*��ʼ�����״̬*/
	XPlayerState = Cast<AXPlayerState>(this->PlayerState);

	/*��ӵ���Ļ*/
	MainWidget->AddToViewport();

	/*�ж��������Ƿ���Ч*/
	if (XCharacter->XWeaponClass) {

		/*������������*/
		XWeapon = GetWorld()->SpawnActor<AWeapon>(XCharacter->XWeaponClass);

		/*�����󶨹���*/
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

		/* ������ */
		XWeapon->AttachToComponent(XCharacter->GetMesh(), AttachmentRule, TEXT("hand_rSocket"));

		// �������ص��¼�
		XWeapon->CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AXPlayerController::WeaponOverlapDamage);
	}

	/*��ʼ�����״̬��ֵ*/
	InitState();

	/*��ʼ��UI*/
	InitUI();

	/*��ʼ����ť����¼�*/
	InitWidgetEvent();

	IceStoneCurrentCD = 0;

	IceStoneTotalCD = 5.f;
}

/* ������ؼ� */
void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*������*/
	InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRight);
}

/*ǰ���ƶ�*/
void AXPlayerController::MoveForward(float Speed)
{
	// ��ȡ�������Ƕ�
	FRotator Rotation = GetControlRotation();

	/*����ƫ���Ƕ�*/
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/*��ȡ�ƶ�����*/
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	/*�ڸ÷������λ��*/
	XCharacter->AddMovementInput(Direction, Speed);
}

/*�����ƶ�*/
void AXPlayerController::MoveRight(float Speed)
{
	// ��ȡ�������Ƕ�
	FRotator Rotation = GetControlRotation();

	/*����ƫ���Ƕ�*/
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/*��ȡ�ƶ�����*/
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	/*�ڸ÷������λ��*/
	XCharacter->AddMovementInput(Direction, Speed);
}

/* �ؼ���ť��ʼ���¼����� */
void AXPlayerController::InitWidgetEvent()
{
	/* ���������ť �����жϰ�ť�Ƿ���� */
	if (MainWidget->Button_Attack) {

		// ������ť���¼�
		MainWidget->Button_Attack->OnClicked.AddDynamic(this, &AXPlayerController::AttackBtnOnClickedEvent);
	}

	// �������֮ʯ���ܰ�ť
	if (MainWidget->Button_IceStone)
	{
		MainWidget->Button_IceStone->OnClicked.AddDynamic(this, &AXPlayerController::IceStoneBtnOnClickedEvent);
	}

	// �ָ����ܰ��¼�
	if (MainWidget->Button_Cure)
	{
		// MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnclickedEvent);
		// Ѫ������ʱ�ָ����ܲ�������
		if( XPlayerState->GetCurrentHP() < XCharacter->TotalHP)
		{
			MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnclickedEvent);
		}
	}

	// ����֮�⼼��
	if(MainWidget->Button_Thunder)
	{
		MainWidget->Button_Thunder->OnClicked.AddDynamic(this, &AXPlayerController::ThunderBtnOnClickedEvent);
	}

	// �޾�֮�м���
	if (MainWidget->Button_XBlade)
	{
		MainWidget->Button_XBlade->OnClicked.AddDynamic(this, &AXPlayerController::XBladeBtnOnClickedEvent);
	}

	// �����ɫ��Ϣ����¼�
	if (MainWidget->Button_Package)
	{
		MainWidget->Button_Package->OnClicked.AddDynamic(this, &AXPlayerController::CharacterBtnOnClickedEvent);
	}
}

/*������ť����¼�*/
void AXPlayerController::AttackBtnOnClickedEvent()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Attack"));

	/*�жϵ�ǰ��̫���Ƿ����ڲ���*/
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}

	/* �������������̫�� */
	UAnimMontage* SerialAttackMontage = XCharacter->SeriorAttackMontage;

	/*��õ�ǰ���ŵĶ���Ƭ��*/
	FName CurrentSection = XAnimInstance->Montage_GetCurrentSection(SerialAttackMontage);

	// ��������
	LockAI();
	
	if (CurrentSection.IsNone())
	{
		/*���ŵ�һ�ζ���*/
		XAnimInstance->Montage_Play(SerialAttackMontage);
	} 
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[0]) && XAnimInstance->bIsEnableSecondAttack)
	{
		/*���ŵڶ��ζ���*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[1]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[1]) && XAnimInstance->bIsEnableThreeAttack)
	{
		/*���ŵ����ζ���*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[2]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[2]) && XAnimInstance->bIsEnableFourAttack)
	{
		/*���ŵ��Ķζ���*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[3]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[3]) && XAnimInstance->bIsEnableFiveAttack)
	{
		/*���ŵ���ζ���*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[4]);
	}
}

// �ͷź���֮ʯ����
void AXPlayerController::IceStoneBtnOnClickedEvent()
{
	// �жϺ���֮ʯ���ܶ����Ƿ����ڲ���
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// �жϵ�ǰħ��ֵ�Ƿ�����
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		// ����������
		LockAI();
		
		// �����ͷż��ܶ���
		XAnimInstance->Montage_Play(XCharacter->IceStoneMontage, 1.f);

		// ������ȴ
		XCharacter->GetWorldTimerManager().SetTimer(IceStoneTimer, this, &AXPlayerController::IceStoneCallback, .1f, true);

		// ���õ�ǰ��ȴʱ��
		IceStoneCurrentCD = IceStoneTotalCD;
	}
}

// ����֮ʯ��ȴ�ص�����
void AXPlayerController::IceStoneCallback()
{
	if (IceStoneCurrentCD <= 0)
	{
		// ���ؽ�����
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Hidden);

		// ���ؼ�ʱ����
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Hidden);

		// �����ʱ��
		XCharacter->GetWorldTimerManager().ClearTimer(IceStoneTimer);
	} else
	{
		// ��ʾ������
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Visible);

		// ��ʾ��ʱ����
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Visible);

		// ���ðٷֱ�
		MainWidget->IceStoneCDBar->SetPercent(IceStoneCurrentCD/IceStoneTotalCD);
		
		// ��������
		MainWidget->IceStoneCDText->SetText(FText::FromString(FString::SanitizeFloat(IceStoneCurrentCD, 1)));

		IceStoneCurrentCD = IceStoneCurrentCD - .1f;
	}
}

// �ָ�����
void AXPlayerController::CureBtnOnclickedEvent()
{
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	if (XPlayerState->GetCurrentMP() >= 15.f)
	{
		// �����ͷż��ܶ���
		XAnimInstance->Montage_Play(XCharacter->CuteMontage, 1.f);
	}
}

// �ͷ�����֮�⼼��
void AXPlayerController::ThunderBtnOnClickedEvent()
{
	// �жϼ��ܶ����Ƿ����ڲ���
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// �жϵ�ǰħ��ֵ�Ƿ�����
	if (XPlayerState->GetCurrentMP() >= 20.f)
	{
		// �����ͷż��ܶ���
		XAnimInstance->Montage_Play(XCharacter->ThunderMontage, 1.f);
	}
}

// �ͷ��޾�֮�м���
void AXPlayerController::XBladeBtnOnClickedEvent()
{
	// �жϼ��ܶ����Ƿ����ڲ���
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// �жϵ�ǰħ��ֵ�Ƿ�����
	if (XPlayerState->GetCurrentMP() >= 50.f)
	{
		// �����ͷż��ܶ���
		XAnimInstance->Montage_Play(XCharacter->XBladeMontage, 1.f);
	}
}

/*��ʼ�����״̬��ֵ*/
void AXPlayerController::InitState()
{
	/*���õ�ǰHP*/
	XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	/*���õ�ǰMP*/
	XPlayerState->SetCurrentMP(XCharacter->TotalMP);
	/*���ù����˺�*/
	XPlayerState->SetAttackDamage(XCharacter->NormalAttack);
}

/*��ʼ��UI*/
void AXPlayerController::InitUI()
{
	/*�ж�HP*/
	if (MainWidget->ProgressBar_HP)
	{
		/*����HP�ٷֱ�*/
		MainWidget->ProgressBar_HP->SetPercent(XPlayerState->GetCurrentHP() / XCharacter->TotalHP);
	}

	/*�ж�MP*/
	if (MainWidget->ProgressBar_MP) {
		/*����MP�ٷֱ�*/
		MainWidget->ProgressBar_MP->SetPercent(XPlayerState->GetCurrentMP() / XCharacter->TotalMP);
	}
}
// �����˺�
void AXPlayerController::WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ж������Ƿ��ڹ����˺�����״̬
	if(XAnimInstance->bIsAttacking)
	{
		// GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Blue, TEXT("Damage"));
		UGameplayStatics::ApplyDamage(OtherActor, XPlayerState->GetAttackDamage(), this, XCharacter, nullptr);
	}
}

// ��������
void AXPlayerController::LockAI()
{
	FVector Location = XCharacter->GetActorLocation();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), AiArray);

	int AiNum = AiArray.Num();
	if (AiNum > 0)
	{
		float MinDistance = FVector::Dist(Location, AiArray[0]->GetActorLocation());

		AActor* MinActor = AiArray[0];

		for (int i = 0; i < AiNum; i++)
		{

			if (Cast<AAICharacter>(AiArray[i])->bIsDead)
			{
				continue;
			}

			float TmpDistance = FVector::Dist(Location, AiArray[i]->GetActorLocation());

			if (MinDistance >= TmpDistance)
			{
				MinDistance = TmpDistance;
				MinActor = AiArray[i];
			}
		}

		if (MinDistance <= 400)
		{

			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Location, MinActor->GetActorLocation());

			Rotation.Pitch = XCharacter->GetCapsuleComponent()->GetComponentRotation().Pitch;
			Rotation.Roll = XCharacter->GetCapsuleComponent()->GetComponentRotation().Roll;

			XCharacter->GetCapsuleComponent()->SetRelativeRotation(Rotation);
		}
	}
}

// �����ɫ��Ϣ����¼�
void AXPlayerController::CharacterBtnOnClickedEvent()
{
	// ��ձ�������
	CharacterWidget->ScrollBox->ClearChildren();

	// ������Ʒ����
	for (int i = 0; i < XCharacter->PickupArray.Num(); i++)
	{
		// ��Ʒ��Ϣ
		FPickupInfo Info = XCharacter->PickupArray[i];

		// ����Item
		UBagItemWidget* ItemWidget = CreateWidget<UBagItemWidget>(GetGameInstance(), LoadClass<UBagItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_BagItem.BP_BagItem_C'")));

		// ������Ϣ
		ItemWidget->PickUpID = Info.ID;

		ItemWidget->Name->SetText(Info.Name);

		ItemWidget->Pic->SetBrushFromTexture(Info.Pic);

		ItemWidget->Desc->SetText(Info.Desc);
		
		ItemWidget->InfoType = Info.Type;

		ItemWidget->Num = Info.Num;

		// ��ӵ�������������
		CharacterWidget->ScrollBox->AddChild(ItemWidget);
	}
	
	/* ��ӵ��ӿ� */
	CharacterWidget->AddToViewport();
}
