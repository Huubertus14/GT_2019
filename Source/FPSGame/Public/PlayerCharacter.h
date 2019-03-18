// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;

UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	TArray<AResource*> Resources;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AResource> toCreate;

	UFUNCTION()
	bool Spawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PerformMineCast();
};
