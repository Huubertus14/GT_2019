// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Ore.h"
#include "PickUpItem.h"
#include "FPSHUD.h"
#include "PlayerCharacter.generated.h"



class UCameraComponent;

UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	UPROPERTY(Replicated)
	int hudCountDown = 60;
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(Replicated)
	TArray<int32> Resources;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* HitBoxComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* MeshShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshDagger;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //UBoxComponent* HitBoxDetection;
	
	float Life;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AArrow> arrowToCreate;

	//Methode called when the player is hit
	void HitPlayer(float damage);

	//Method called when the player is healed
	void HealPlayer(float heal);

	//The result returned when a raycast is cast.
	FHitResult* HitResult;

	/** stamina accessor */
	UFUNCTION(BlueprintPure, Category = "Stamina")
		float GetCurrentStam();

	UFUNCTION(BlueprintPure, Category = "Stamina")
		float GetCurrentMaxStam();

	/** health accessor */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentLife();

	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceZero();
	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceOne();
	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceTwo();
private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float lifeCap;
	
	UPROPERTY(Replicated, EditAnywhere, Category = "Health")
	float life;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(Replicated ,EditAnywhere, Category = "Stamina")
	float CurrentMaxStamina;
		
	UPROPERTY(Replicated, EditAnywhere, Category = "Stamina")
		float CurrentStamina;


	UFUNCTION()
		void EnergizePlayer(float amount);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//This is an array which contains all the drop weapons a player can possibly have
	UPROPERTY(EditAnywhere, Category = "Drop Weapons")
	TArray<TSubclassOf<class APickUpItem>> dropWeapons;

	int currentWeaponID;

	UFUNCTION(Server, Reliable, WithValidation)
	void DropWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void RightMouseClick();


public:

	UFUNCTION(Server, Reliable, WithValidation)
	void LeaveGame();

	UFUNCTION()
	void DestroyPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void PerformMineCast();

	UFUNCTION(Server, Reliable, WithValidation)
		void PerformHitCast();

	void WeaponVisibility();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void WeaponSlot1();

	UFUNCTION(Server, Reliable, WithValidation)
	void WeaponSlot2();

	UFUNCTION(Server, Reliable, WithValidation)
	void WeaponSlot3();

	UFUNCTION(Server, Reliable, WithValidation)
	void WeaponSlot4();

	UFUNCTION(Server, Reliable, WithValidation)
	void WeaponSlot5();

	UFUNCTION(Server, Reliable, WithValidation)
		void DrawArrow();

	//Arrow variables
	UPROPERTY(Replicated)
		float power;
	UPROPERTY(Replicated)
		bool isDrawn;

	UPROPERTY(Replicated)
		int equipedWeapon;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "isBow")
	bool isBow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "is2H")
	bool is2H;
};
