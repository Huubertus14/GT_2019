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
	APlayerCharacter();

	UPROPERTY(Replicated)
		TArray<int32> m_r_resources;

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

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AArrow> arrowToCreate;

	//Methode called when the player is hit
	void HitPlayer(float damage);

	//Method called when the player is healed
	void HealPlayer(float heal);

	void SharePlayerPitch();

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

	/** resources accessor */
	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceZero();
	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceOne();
	UFUNCTION(BlueprintPure, Category = "Resources")
		FText GetResourceTwo();

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float m_lifeCap;
	
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Health")
		float m_r_life;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
		float m_maxStamina;

	UPROPERTY(Replicated, VisibleAnywhere, Category = "Stamina")
		float m_r_currentMaxStamina;
		
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Stamina")
		float m_r_currentStamina;

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
		void ServerDropWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* cameraComponent;

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRightMouseClick();


public:

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerLeaveGame();
		
	UFUNCTION()
		void DestroyPlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void UpdateLifeStatus();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPerformMineCast();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPerformHitCast();

	//sets all weapons invisible
	void WeaponVisibility();
	
	/** weaponSwitching */
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
		void ServerDrawArrow();

	//Arrow variables
	UPROPERTY(Replicated)
		float m_r_power;
	UPROPERTY(Replicated)
		bool m_r_isDrawn;

	//the weapon the player is wielding with its id 
	UPROPERTY(Replicated)
		int equipedWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bowEquiped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool twoHanderEquiped;

	bool UpdateBowTension(float DeltaTime);

	void RegainEnergy(float DeltaTime);
};
