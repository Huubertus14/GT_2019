// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

/**
 *
 */
UCLASS()
class FPSGAME_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
		UFPSGameInstance(const FObjectInitializer & ObjectInitializer);

		virtual void Init();
};