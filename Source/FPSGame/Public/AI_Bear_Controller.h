// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "AI_Bear_Controller.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AAI_Bear_Controller : public AAIController
{
	GENERATED_BODY()

	public:

		void BeginPlay() override;

	private:

		UPROPERTY()
			TArray<AActor*> waypoints;

		UFUNCTION()
			ATargetPoint* GetRandomWaypoint();

		UFUNCTION()
			void GoToRandomWaypoint();

	
};
