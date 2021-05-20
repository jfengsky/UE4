// Fill out your copyright notice in the Description page of Project Settings.

#include "XPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Character/Skill/IceStone.h"
#include "Pickup/ItemInfo.h"
#include "UI/BagItemWidget.h"
#include "AI/AICharacter.h"

/** ��Ϸ��ʼ���õķ��� */
void AXPlayerController::BeginPlay()
{
	/** ������ʾ��� */
	bShowMouseCursor = true;

	CharacterWidget = CreateWidget<UCharacterWidget>(GetGameInstance(), LoadClass<UCharacterWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_CharacterWidget.BP_CharacterWidget_C'")));
	/** ��ʼ��������UI */
	MainWidget = CreateWidget<UMainUserWidget>(GetGameInstance(), LoadClass<UMainUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_MainUserWidget.BP_MainUserWidget_C'")));
	/** ��ӵ��ӿ� */
	MainWidget->AddToViewport();
	/** ��ʼ��UI */
	UpdateUI();

	/** �ж��������Ƿ���Ч */
	if (XCharacter->XWeaponClass)
	{
		/** ����һ���������� */
		XWeapon = GetWorld()->SpawnActor<AWeapon>(XCharacter->XWeaponClass);
		/** �󶨹��� */
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		/** ������ */
		XWeapon->AttachToComponent(XCharacter->GetMesh(), AttachmentRules, TEXT("hand_rSocket"));
		/** �������ص��¼� */
		XWeapon->CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AXPlayerController::WeaponOverlapDamage);
	}

	/** ��ʼ����ť����¼� */
	InitWidgetEvent();

	/** ��ʼ����ȴʱ�� */
	IceStoneTotalCD = 5.f;
	IceStoneCurrentCD = 0.f;
	/** ��ʼ��Msg��ȴʱ�� */
	MsgTotalCD = 2.f;
	MsgCurrentCD = 0.f;
}

/** ������ؼ� */
void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/** ������ */
	InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRight);
}

/** ��д��Character�ķ��� */
void AXPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);
	
	/** ��ʼ��Ӣ�۽�ɫ���� */
	XCharacter = Cast<AXCharacter>(aPawn);
	/** ��ʼ������ʵ�� */
	XAnimInstance = Cast<UXAnimInstance>(XCharacter->GetMesh()->GetAnimInstance());
	/** ��ʼ�����״̬ */
	XPlayerState = Cast<AXPlayerState>(this->PlayerState);
	/** ��ʼ�����״̬��ֵ */
	InitState();
}

/** ǰ���ƶ� */
void AXPlayerController::MoveForward(float Speed)
{
	/** ��ȡ�������ĽǶ� */
	FRotator Rotation = GetControlRotation();
	/** ����ƫ���� */
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/** ��ȡ�ƶ��ķ��� */
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	/** �ڸ÷������λ�� */
	XCharacter->AddMovementInput(Direction, Speed);
}

/** �����ƶ� */
void AXPlayerController::MoveRight(float Speed)
{
	/** ��ȡ�������ĽǶ� */
	FRotator Rotation = GetControlRotation();
	/** ����ƫ���� */
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/** ��ȡ�ƶ��ķ��� */
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	/** �ڸ÷������λ�� */
	XCharacter->AddMovementInput(Direction, Speed);
}

/** ��ʼ�����״̬ */
void AXPlayerController::InitState()
{
	/** ����һ�µ�ǰ��HP */
	XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	/** ����һ�µ�ǰ��MP */
	XPlayerState->SetCurrentMP(XCharacter->TotalMP);
	/** ����һ���չ������˺� */
	XPlayerState->SetAttackDamage(XCharacter->NoramlAttack);
}

/** ��ʼ��UI */
void AXPlayerController::UpdateUI()
{
	/** ����HP */
	if (MainWidget->ProgressBar_HP)
	{
		MainWidget->ProgressBar_HP->SetPercent(1.0 - (XPlayerState->GetCurrentHP() / XCharacter->TotalHP));
	}
	/** ����MP */
	if (MainWidget->ProgressBar_MP)
	{
		MainWidget->ProgressBar_MP->SetPercent(1.0 - (XPlayerState->GetCurrentMP() / XCharacter->TotalMP));
	}
}

/** �����˺����� */
void AXPlayerController::WeaponOverlapDamage(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	/** �ж������Ƿ��ڹ���״̬ */
	if (XAnimInstance->bIsAttacking)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Overlap...");
		UGameplayStatics::ApplyDamage(OtherActor, XPlayerState->GetAttackDamage(), this, XCharacter, nullptr);
	}
}

/** �������˷��� */
void AXPlayerController::LockAI()
{
	/** ��ȡ�Լ���λ�� */
	FVector Location = XCharacter->GetActorLocation();
	/** ��ȡ���еĵ����б� */
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAICharacter::StaticClass(), AiArray);
	/** �жϵ������� */
	int AiNum = AiArray.Num();
	if (AiNum > 0)
	{
		/** ��ȡĬ��������� */
		float MinDistance = FVector::Dist(Location, AiArray[0]->GetActorLocation());
		/** ������������AI */
		AActor* MinActor = AiArray[0];
		/** �������е��� */
		for (int i = 0; i < AiNum; i++)
		{
			/** �жϵ����Ƿ��Ѿ����� */
			if (Cast<AAICharacter>(AiArray[i])->bIsDead)
			{
				continue;
			}
			/** ��ȡ���� */
			float TmpDistance = FVector::Dist(Location, AiArray[i]->GetActorLocation());
			/** �ж�������� */
			if (MinDistance >= TmpDistance)
			{
				MinDistance = TmpDistance;
				MinActor = AiArray[i];
			}
		}
		/** �жϾ����Ƿ��������㹻�Ľ� */
		if (MinDistance <= 400)
		{
			/** ����Rotationֻ������ת */
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Location, MinActor->GetActorLocation());
			/** �޸�Rotation */
			Rotation.Pitch = XCharacter->GetCapsuleComponent()->GetComponentRotation().Pitch;
			Rotation.Roll = XCharacter->GetCapsuleComponent()->GetComponentRotation().Roll;
			/** ������ҽ����峯�� */
			XCharacter->GetCapsuleComponent()->SetRelativeRotation(Rotation);
		}
	}
}

/** �ؼ���ť�¼���ʼ������ */
void AXPlayerController::InitWidgetEvent()
{
	/** ������ť����¼��� */
	if (MainWidget->Button_Attack)
	{
		MainWidget->Button_Attack->OnClicked.AddDynamic(this, &AXPlayerController::AttackBtnOnClickedEvent);
	}
	/** ����֮ʯ��ť����¼��� */
	if (MainWidget->Button_IceStone)
	{
		MainWidget->Button_IceStone->OnClicked.AddDynamic(this, &AXPlayerController::IceStoneBtnOnClickedEvent);
	}
	/** �ָ�֮����ť����¼��� */
	if (MainWidget->Button_Cure)
	{
		MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnClickedEvent);
	}
	/** ����֮�ⰴť����¼��� */
	if (MainWidget->Button_Thunder)
	{
		MainWidget->Button_Thunder->OnClicked.AddDynamic(this, &AXPlayerController::ThunderBtnOnClickedEvent);
	}
	/** �޾�֮�а�ť����¼��� */
	if (MainWidget->Button_XBlade)
	{
		MainWidget->Button_XBlade->OnClicked.AddDynamic(this, &AXPlayerController::XBladeBtnOnClickedEvent);
	}
	/** �����ɫ��Ϣ��ť����¼��� */
	if (MainWidget->Button_Package)
	{
		MainWidget->Button_Package->OnClicked.AddDynamic(this, &AXPlayerController::CharacterBtnOnClickedEvent);
	}
}

/** ������ť����¼� */
void AXPlayerController::AttackBtnOnClickedEvent()
{
	/** �жϵ�ǰ��̫���Ƿ����ڲ���,������ڲ�������ֹ */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** �������������̫�� */
	UAnimMontage* SerialAttakMontage = XCharacter->SerialAttackMontage;
	/** ��õ�ǰ���ŵĽ� */
	FName CurrentSection = XAnimInstance->Montage_GetCurrentSection(SerialAttakMontage);
	/** �������� */
	LockAI();
	/** �ж� */
	if (CurrentSection.IsNone())
	{
		/** Ĭ�ϲ��ŵ�һ���� */
		XAnimInstance->Montage_Play(SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("FirstSection")) && XAnimInstance->bIsEnableSecondAttack)
	{
		/** ���ŵڶ����� */
		XAnimInstance->Montage_JumpToSection(FName("SecondSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("SecondSection")) && XAnimInstance->bIsEnableThreeAttack)
	{
		/** ���ŵ������� */
		XAnimInstance->Montage_JumpToSection(FName("ThreeSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("ThreeSection")) && XAnimInstance->bIsEnableFourAttack)
	{
		/** ���ŵ��ĸ��� */
		XAnimInstance->Montage_JumpToSection(FName("FourSection"), SerialAttakMontage);
	}
	else if (CurrentSection.IsEqual(FName("FourSection")) && XAnimInstance->bIsEnableFiveAttack)
	{
		/** ���ŵ������ */
		XAnimInstance->Montage_JumpToSection(FName("FiveSection"), SerialAttakMontage);
	}
}

/** ����֮ʯ���ܵ���¼� */
void AXPlayerController::IceStoneBtnOnClickedEvent()
{
	/** �жϺ���֮ʯ��̫���Ƿ����ڲ��� */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** �жϵ�ǰħ��ֵ�Ƿ��㹻 */
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		LockAI();
		XAnimInstance->Montage_Play(XCharacter->IceStoneMontage, 1.f);
		/** ��ʼ�䶨ʱ�� */
		XCharacter->GetWorldTimerManager().SetTimer(IceStoneTimer, this, &AXPlayerController::IceStoneCallback, 1.f, true);
		/** ���õ�ǰ��ȴʱ�� */
		IceStoneCurrentCD = IceStoneTotalCD;
	}
}

/** ����֮ʯ��ʱ���ص����� */
void AXPlayerController::IceStoneCallback()
{
	if (IceStoneCurrentCD == 0.f)
	{
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Hidden);
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Hidden);
		XCharacter->GetWorldTimerManager().ClearTimer(IceStoneTimer);
	}
	else
	{
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Visible);
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Visible);
		MainWidget->IceStoneCDBar->SetPercent(IceStoneCurrentCD / IceStoneTotalCD);
		MainWidget->IceStoneCDText->SetText(FText::FromString(FString::FromInt(IceStoneCurrentCD)+"s"));
		IceStoneCurrentCD--;
	}
}

/** �ָ�֮�����ܵ���¼� */
void AXPlayerController::CureBtnOnClickedEvent()
{
	/** �жϻָ�֮����̫���Ƿ����ڲ��� */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** �жϵ�ǰħ��ֵ�Ƿ��㹻 */
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		if (XPlayerState->GetCurrentHP() < XCharacter->TotalHP)
		{
			XAnimInstance->Montage_Play(XCharacter->CureMontage, 1.f);
		}
		else
		{
			MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
			MainWidget->MsgText->SetText(FText::FromString("HP Is MaxValue"));
			MsgCurrentCD = MsgTotalCD;
			XCharacter->GetWorldTimerManager().SetTimer(MsgTimer, this, &AXPlayerController::MsgTimerCallback, 1.f, true);
		}
	}
	else
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
		MainWidget->MsgText->SetText(FText::FromString("MP Is Not Enough"));
		MsgCurrentCD = MsgTotalCD;
		XCharacter->GetWorldTimerManager().SetTimer(MsgTimer, this, &AXPlayerController::MsgTimerCallback, 1.f, true);
	}
}

/** ����֮�⼼�ܵ���¼� */
void AXPlayerController::ThunderBtnOnClickedEvent()
{
	/** �жϻָ�֮����̫���Ƿ����ڲ��� */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** �жϵ�ǰħ��ֵ�Ƿ��㹻 */
	if (XPlayerState->GetCurrentMP() >= 30.f)
	{
		XAnimInstance->Montage_Play(XCharacter->ThunderMontage, 1.f);
	}
}

/** �޾�֮�м��ܵ���¼� */
void AXPlayerController::XBladeBtnOnClickedEvent()
{
	/** �жϻָ�֮����̫���Ƿ����ڲ��� */
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	/** �жϵ�ǰħ��ֵ�Ƿ��㹻 */
	if (XPlayerState->GetCurrentMP() >= 50.f)
	{
		XAnimInstance->Montage_Play(XCharacter->XBladeMontage, 1.f);
	}
}

/** ��Ϣ��ʾ��ʱ���ص����� */
void AXPlayerController::MsgTimerCallback()
{
	if (MsgCurrentCD == 0.f)
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Hidden);
		XCharacter->GetWorldTimerManager().ClearTimer(MsgTimer);
	}
	else
	{
		MainWidget->MsgText->SetVisibility(ESlateVisibility::Visible);
		MsgCurrentCD--;
	}
}

/** �����ɫ��Ϣ����¼� */
void AXPlayerController::CharacterBtnOnClickedEvent()
{
	/** ��ձ������� */
	CharacterWidget->ScrollBox->ClearChildren();
	/** ������ɫ��Ʒ���� */
	for (int i = 0; i < XCharacter->PickupArray.Num(); i++)
	{
		/** ��Ʒ��Ϣ */
		FPickupInfo Info = XCharacter->PickupArray[i];
		/** ����Item */
		UBagItemWidget* ItemWidget = CreateWidget<UBagItemWidget>(GetGameInstance(), LoadClass<UBagItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_BagItem.BP_BagItem_C'")));
		/** ������Ϣ */
		ItemWidget->PickupId = Info.ID;
		ItemWidget->Name->SetText(Info.Name);
		ItemWidget->Pic->SetBrushFromTexture(Info.Pic);
		ItemWidget->Desc->SetText(Info.Desc);
		ItemWidget->Num = Info.Num;
		ItemWidget->InfoType = Info.Type;
		/** ��ӵ������������� */
		CharacterWidget->ScrollBox->AddChild(ItemWidget);
	}
	/** ��ӵ��ӿ� */
	CharacterWidget->AddToViewport();
}
