// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bow.generated.h"

UCLASS()
class SHOOT_API ABow : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	//handles moving forward/backward
	UFUNCTION()
		void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
		void MoveRight(float Val);

	void DrawArrow();
	void FireArrow();

	FVector CurrentVelocity;
	float power;
	bool isDrawn;
	float spawnTime;
	bool isPressed;
};
