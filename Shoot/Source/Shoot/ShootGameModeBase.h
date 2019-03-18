// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOT_API AShootGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		AShootGameModeBase(const FObjectInitializer& ObjectInitializer);  // Our added constructor

	virtual void StartPlay() override;
};
