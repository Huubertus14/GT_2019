// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickUpThrow.h"
#include "Resource.h"
#include "Ore.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;

UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Location on gun mesh where projectiles should spawn*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/**First person camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Holding Component*/
	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComponent;

public:

	// Sets default values for this character's properties
	APlayerCharacter();
	
	TArray<AResource*> Resources;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AResource> toCreate;

	float Life;

	UFUNCTION()
	bool Spawn();

	AOre* hitTemp;
	FHitResult* HitResult;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

public:	

	UFUNCTION(Server, Reliable, WithValidation)
	void LeaveGame();

	void DestroyPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void PerformMineCast();

	//Arrow functions
	void DrawArrow();
	void FireArrow();

	//Arrow variables
	float power;
	bool isDrawn;
	float spawnTime;
	FRotator arrowRotation;

	/**PickUpThrow functions*/
	void OnAction();
	void ToggleItemPickup();

	/**PickUpThrow variables*/
	APickUpThrow* CurrentItem;

	bool bCanMove;
	bool bHoldingItem;

	FVector HoldingComp;

	FVector Start;
	FVector ForwardVector;
	FVector End;

	FHitResult Hit;

	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;
};
