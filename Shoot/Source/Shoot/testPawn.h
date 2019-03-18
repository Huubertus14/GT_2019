// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "testPawn.generated.h"

UCLASS()
class SHOOT_API AtestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AtestPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();
	void DrawArrow();
	void FireArrow();
	float spawnTime;

	FVector CurrentVelocity;
	bool bGrowing;
	bool isDrawn;
	float power;
};
