// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickUpThrow.h"
#include "Resource.h"
#include "Ore.h"
#include "PickUpThrow.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;

UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* MeshCube;
	/**Grip Trick*/
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* WeaponGrip;

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

	UFUNCTION()
	bool Spawn();

	float Life;

	AOre* hitTemp;
	FHitResult* HitResult;
	APickUpThrow* pickUp;
	

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	/**PickUpThrow functions*/
	void OnAction();
	void ToggleItemPickup();

public:	

	UFUNCTION(Server, Reliable, WithValidation)
	void LeaveGame();

	void DestroyPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* KnifeMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* AxeMesh;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class USkeletalMeshComponent* GetMeshCube() const { return MeshCube; }

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION(Server, Reliable, WithValidation)
	void PerformMineCast();

	UFUNCTION(Server, Reliable, WithValidation)
		void PerformRightClickCast();

	//Arrow functions
	void DrawArrow();
	void FireArrow();

	//Arrow variables
	float power;
	bool isDrawn;
	float spawnTime;
	FRotator arrowRotation;

	/**PickUpThrow variables*/
	APickUpThrow* CurrentItem;

	bool bCanMove;
	bool bHoldingItem;

	FVector HoldingComp;

	FVector Start;
	FVector ForwardVector;
	FVector End;

	FHitResult HitPickup;

	FComponentQueryParams DefaultComponentQueryParams;
	FCollisionResponseParams DefaultResponseParam;
};
