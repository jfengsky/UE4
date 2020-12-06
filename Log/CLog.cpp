// Fill out your copyright notice in the Description page of Project Settings.


#include "CLog.h"


//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%f"), value));


void UCLog::Log(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, message);
}

void UCLog::Log(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("X:%f, Y:%f, Z:%f"), Vector.X, Vector.Y, Vector.Z));
}

void UCLog::Log(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%f"), Value));
}

void UCLog::Log(FRotator Rotator)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Pitch:%f, Yaw:%f, Roll:%f"), Rotator.Pitch, Rotator.Yaw, Rotator.Roll));
}
