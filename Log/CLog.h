// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CLog.generated.h"

/**
 * 
 */
UCLASS()
class TESTLOG_API UCLog : public UObject
{
	GENERATED_BODY()

public:
	static void Log(FString message);

	static void Log(FVector Vector);

	static void Log(float Value);

	static void Log(FRotator Rotator);
};
