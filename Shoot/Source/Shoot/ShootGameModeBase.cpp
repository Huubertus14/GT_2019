// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootGameModeBase.h"
#include "Bow.h"
#include "Engine.h"
AShootGameModeBase::AShootGameModeBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultPawnClass = ABow::StaticClass();
}
void AShootGameModeBase::StartPlay()
{
	Super::StartPlay();


	
}
