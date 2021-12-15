// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EPickupInfoType: uint8
{
	HP UMETA(DisplayName = "HP"),
	MP UMETA(DisplayName = "MP")
};

USTRUCT(BlueprintType)
struct FPickupInfo
{
	GENERATED_USTRUCT_BODY()

	// 物品id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
		uint8 ID;

	// 物品名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
		FText Name;

	// 物品类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
		EPickupInfoType Type;

	// 物品图片
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
		UTexture2D* Pic;

	// 物品描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
		FText Desc;

	// 物品功效 +100血量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")
	float Num;
	
};