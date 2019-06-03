// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameInstance.h"

UFPSGameInstance::UFPSGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

void UFPSGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Init"));
}
