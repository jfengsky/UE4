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

/* 游戏开始调用的方法 */
void AXPlayerController::BeginPlay()
{
	/*显示鼠标指针*/
	bShowMouseCursor = true;

	/*初始化角色对象*/
	XCharacter = Cast<AXCharacter>(GetPawn());

	/*初始化动画实例*/
	XAnimInstance = Cast<UXAnimInstance>(XCharacter->GetMesh()->GetAnimInstance());

	/*初始化主界面*/
	MainWidget = CreateWidget<UMainUserWidget>(GetGameInstance(), LoadClass<UMainUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_MainUserWidget.BP_MainUserWidget_C'")));

	/*初始化人物信息界面*/
	CharacterWidget = CreateWidget<UCharacterWidget>(GetGameInstance(), LoadClass<UCharacterWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_CharacterWidget.BP_CharacterWidget_C'")));
	
	/*初始化玩家状态*/
	XPlayerState = Cast<AXPlayerState>(this->PlayerState);

	/*添加到屏幕*/
	MainWidget->AddToViewport();

	/*判断武器类是否有效*/
	if (XCharacter->XWeaponClass) {

		/*生成武器对象*/
		XWeapon = GetWorld()->SpawnActor<AWeapon>(XCharacter->XWeaponClass);

		/*武器绑定规则*/
		FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

		/* 绑定武器 */
		XWeapon->AttachToComponent(XCharacter->GetMesh(), AttachmentRule, TEXT("hand_rSocket"));

		// 绑定武器重叠事件
		XWeapon->CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AXPlayerController::WeaponOverlapDamage);
	}

	/*初始化玩家状态数值*/
	InitState();

	/*初始化UI*/
	InitUI();

	/*初始化按钮点击事件*/
	InitWidgetEvent();

	IceStoneCurrentCD = 0;

	IceStoneTotalCD = 5.f;
}

/* 绑定输入控件 */
void AXPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*绑定输入*/
	InputComponent->BindAxis("MoveForward", this, &AXPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AXPlayerController::MoveRight);
}

/*前后移动*/
void AXPlayerController::MoveForward(float Speed)
{
	// 获取控制器角度
	FRotator Rotation = GetControlRotation();

	/*创建偏航角度*/
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/*获取移动方向*/
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	/*在该方向添加位移*/
	XCharacter->AddMovementInput(Direction, Speed);
}

/*左右移动*/
void AXPlayerController::MoveRight(float Speed)
{
	// 获取控制器角度
	FRotator Rotation = GetControlRotation();

	/*创建偏航角度*/
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	/*获取移动方向*/
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	/*在该方向添加位移*/
	XCharacter->AddMovementInput(Direction, Speed);
}

/* 控件按钮初始化事件方法 */
void AXPlayerController::InitWidgetEvent()
{
	/* 点击攻击按钮 首先判断按钮是否存在 */
	if (MainWidget->Button_Attack) {

		// 攻击按钮绑定事件
		MainWidget->Button_Attack->OnClicked.AddDynamic(this, &AXPlayerController::AttackBtnOnClickedEvent);
	}

	// 点击寒冰之石技能按钮
	if (MainWidget->Button_IceStone)
	{
		MainWidget->Button_IceStone->OnClicked.AddDynamic(this, &AXPlayerController::IceStoneBtnOnClickedEvent);
	}

	// 恢复技能绑定事件
	if (MainWidget->Button_Cure)
	{
		// MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnclickedEvent);
		// 血量不满时恢复技能才起作用
		if( XPlayerState->GetCurrentHP() < XCharacter->TotalHP)
		{
			MainWidget->Button_Cure->OnClicked.AddDynamic(this, &AXPlayerController::CureBtnOnclickedEvent);
		}
	}

	// 雷霆之光技能
	if(MainWidget->Button_Thunder)
	{
		MainWidget->Button_Thunder->OnClicked.AddDynamic(this, &AXPlayerController::ThunderBtnOnClickedEvent);
	}

	// 无尽之刃技能
	if (MainWidget->Button_XBlade)
	{
		MainWidget->Button_XBlade->OnClicked.AddDynamic(this, &AXPlayerController::XBladeBtnOnClickedEvent);
	}

	// 人物角色信息点击事件
	if (MainWidget->Button_Package)
	{
		MainWidget->Button_Package->OnClicked.AddDynamic(this, &AXPlayerController::CharacterBtnOnClickedEvent);
	}
}

/*攻击按钮点击事件*/
void AXPlayerController::AttackBtnOnClickedEvent()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Attack"));

	/*判断当前蒙太奇是否正在播放*/
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}

	/* 获得连击动画蒙太奇 */
	UAnimMontage* SerialAttackMontage = XCharacter->SeriorAttackMontage;

	/*获得当前播放的动画片段*/
	FName CurrentSection = XAnimInstance->Montage_GetCurrentSection(SerialAttackMontage);

	// 锁定敌人
	LockAI();
	
	if (CurrentSection.IsNone())
	{
		/*播放第一段动画*/
		XAnimInstance->Montage_Play(SerialAttackMontage);
	} 
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[0]) && XAnimInstance->bIsEnableSecondAttack)
	{
		/*播放第二段动画*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[1]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[1]) && XAnimInstance->bIsEnableThreeAttack)
	{
		/*播放第三段动画*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[2]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[2]) && XAnimInstance->bIsEnableFourAttack)
	{
		/*播放第四段动画*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[3]);
	}
	else if (CurrentSection.IsEqual(XAnimInstance->AttackSections[3]) && XAnimInstance->bIsEnableFiveAttack)
	{
		/*播放第五段动画*/
		XAnimInstance->Montage_JumpToSection(XAnimInstance->AttackSections[4]);
	}
}

// 释放寒冰之石技能
void AXPlayerController::IceStoneBtnOnClickedEvent()
{
	// 判断寒冰之石技能动画是否正在播放
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// 判断当前魔法值是否满足
	if (XPlayerState->GetCurrentMP() >= 10.f)
	{
		// 先锁定敌人
		LockAI();
		
		// 播放释放技能动画
		XAnimInstance->Montage_Play(XCharacter->IceStoneMontage, 1.f);

		// 技能冷却
		XCharacter->GetWorldTimerManager().SetTimer(IceStoneTimer, this, &AXPlayerController::IceStoneCallback, .1f, true);

		// 设置当前冷却时间
		IceStoneCurrentCD = IceStoneTotalCD;
	}
}

// 寒冰之石冷却回调方法
void AXPlayerController::IceStoneCallback()
{
	if (IceStoneCurrentCD <= 0)
	{
		// 隐藏进度条
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Hidden);

		// 隐藏计时文字
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Hidden);

		// 清除定时器
		XCharacter->GetWorldTimerManager().ClearTimer(IceStoneTimer);
	} else
	{
		// 显示进度条
		MainWidget->IceStoneCDBar->SetVisibility(ESlateVisibility::Visible);

		// 显示计时文字
		MainWidget->IceStoneCDText->SetVisibility(ESlateVisibility::Visible);

		// 设置百分比
		MainWidget->IceStoneCDBar->SetPercent(IceStoneCurrentCD/IceStoneTotalCD);
		
		// 设置文字
		MainWidget->IceStoneCDText->SetText(FText::FromString(FString::SanitizeFloat(IceStoneCurrentCD, 1)));

		IceStoneCurrentCD = IceStoneCurrentCD - .1f;
	}
}

// 恢复技能
void AXPlayerController::CureBtnOnclickedEvent()
{
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	if (XPlayerState->GetCurrentMP() >= 15.f)
	{
		// 播放释放技能动画
		XAnimInstance->Montage_Play(XCharacter->CuteMontage, 1.f);
	}
}

// 释放雷霆之光技能
void AXPlayerController::ThunderBtnOnClickedEvent()
{
	// 判断技能动画是否正在播放
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// 判断当前魔法值是否满足
	if (XPlayerState->GetCurrentMP() >= 20.f)
	{
		// 播放释放技能动画
		XAnimInstance->Montage_Play(XCharacter->ThunderMontage, 1.f);
	}
}

// 释放无尽之刃技能
void AXPlayerController::XBladeBtnOnClickedEvent()
{
	// 判断技能动画是否正在播放
	if (XAnimInstance->bIsPlaying)
	{
		return;
	}
	// 判断当前魔法值是否满足
	if (XPlayerState->GetCurrentMP() >= 50.f)
	{
		// 播放释放技能动画
		XAnimInstance->Montage_Play(XCharacter->XBladeMontage, 1.f);
	}
}

/*初始化玩家状态数值*/
void AXPlayerController::InitState()
{
	/*设置当前HP*/
	XPlayerState->SetCurrentHP(XCharacter->TotalHP);
	/*设置当前MP*/
	XPlayerState->SetCurrentMP(XCharacter->TotalMP);
	/*设置攻击伤害*/
	XPlayerState->SetAttackDamage(XCharacter->NormalAttack);
}

/*初始化UI*/
void AXPlayerController::InitUI()
{
	/*判断HP*/
	if (MainWidget->ProgressBar_HP)
	{
		/*设置HP百分比*/
		MainWidget->ProgressBar_HP->SetPercent(XPlayerState->GetCurrentHP() / XCharacter->TotalHP);
	}

	/*判断MP*/
	if (MainWidget->ProgressBar_MP) {
		/*设置MP百分比*/
		MainWidget->ProgressBar_MP->SetPercent(XPlayerState->GetCurrentMP() / XCharacter->TotalMP);
	}
}
// 武器伤害
void AXPlayerController::WeaponOverlapDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 判断武器是否处于攻击伤害计算状态
	if(XAnimInstance->bIsAttacking)
	{
		// GEngine->AddOnScreenDebugMessage(-1,2.f, FColor::Blue, TEXT("Damage"));
		UGameplayStatics::ApplyDamage(OtherActor, XPlayerState->GetAttackDamage(), this, XCharacter, nullptr);
	}
}

// 锁定敌人
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

// 人物角色信息点击事件
void AXPlayerController::CharacterBtnOnClickedEvent()
{
	// 清空背包盒子
	CharacterWidget->ScrollBox->ClearChildren();

	// 遍历物品数组
	for (int i = 0; i < XCharacter->PickupArray.Num(); i++)
	{
		// 物品信息
		FPickupInfo Info = XCharacter->PickupArray[i];

		// 创建Item
		UBagItemWidget* ItemWidget = CreateWidget<UBagItemWidget>(GetGameInstance(), LoadClass<UBagItemWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UI/BP_BagItem.BP_BagItem_C'")));

		// 设置信息
		ItemWidget->PickUpID = Info.ID;

		ItemWidget->Name->SetText(Info.Name);

		ItemWidget->Pic->SetBrushFromTexture(Info.Pic);

		ItemWidget->Desc->SetText(Info.Desc);
		
		ItemWidget->InfoType = Info.Type;

		ItemWidget->Num = Info.Num;

		// 添加到背包滚动盒子
		CharacterWidget->ScrollBox->AddChild(ItemWidget);
	}
	
	/* 添加到视口 */
	CharacterWidget->AddToViewport();
}
