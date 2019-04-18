// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "GameFramework/Character.h"
#include "Ore.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshPit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshBow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshAxe;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshPickaxe;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshSword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* Mesh2HSword;

	

	float Life;

	UFUNCTION()
	bool Spawn();

	AOre* hitTemp;
	FHitResult* HitResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

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

	//input functions
	void DrawArrow();
	void FireArrow();
	void WeaponSlot1();
	void WeaponSlot2();
	void WeaponSlot3();
	void WeaponSlot4();
	void WeaponSlot5();

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "isBow")
	bool isBow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "is2H")
	bool is2H;

	//Arrow variables
	float power;
	bool isDrawn;
	float spawnTime;
	FRotator arrowRotation;
};
