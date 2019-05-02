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

//! The player class
/*! 
 *This class will handle all the things a player needs to do and say to the server
 *Like movement, shooting arrow, keep track of score etc.
*/
UCLASS()
class FPSGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/** The replicated recources */
	UPROPERTY(Replicated)
		TArray<int32> r_resources;

	/** The hitbox of the player*/
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* HitBoxComponent;

	/** The model of the player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* MeshPit;

	/** Mesh of the bow which it will hold
	 *bow is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshBow;

	/** The mesh of the arrow which is seen in the hands of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshArrow;

	/** Mesh of the Axe which it will hold
	 *Axe is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* MeshAxe;

	/** Mesh of the Pickaxe which it will hold
	 *PickAxe is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		USkeletalMeshComponent* MeshPickaxe;

	/** Mesh of the sword which it will hold
	 *sword is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshSword;

	/** Mesh of the 2hSword which it will hold
	 *2hSword is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh2HSword;

	/** Mesh of the shield which it will hold
	 *shield is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshShield;

	/** Mesh of the dagger which it will hold
	 *dagger is defined in the BP of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshDagger;

	/** Actor of the arrow which it will shoot
	 *Arrow is defined in the BP of the player */
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AArrow> arrowToCreate;

	/**Methode called when the player is hit*/
	void HitPlayer(float damage);

	/**Method called when the player is healed*/
	void HealPlayer(float heal);

	/**Crucial method to fix the pitch rotation of the player*/
	void SharePlayerPitch();

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

	/**Replicated arrow power
	 * This increases power when draw is true, also drains stamina
	 * The power is given to the arrow when it launches
	*/
	UPROPERTY(Replicated)
		float m_r_power;

	/**Replicated draw value*/
	UPROPERTY(Replicated)
		bool m_r_isDrawn;

	/**The result returned when a raycast is cast.*/
	FHitResult* m_hitResult;
	
	/** This value indicates the max life of a player*/
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float m_lifeCap;

	/** This value indicates the max replicated life of a player*/
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Health")
		float m_r_life;

	/** This value indicates the max stamina player can have*/
	UPROPERTY(VisibleAnywhere, Category = "Stamina")
		float m_maxStamina;

	/** This value indicates the current replicated max stamina of a player*/
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Stamina")
		float m_r_currentMaxStamina;

	/** This value indicates the current replicated stamina of a player*/
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Stamina")
		float m_r_currentStamina;

	
protected:
	/**Called when the game starts or when spawned*/
	virtual void BeginPlay() override;

	/**This is an array which contains all the drop weapons a player can possibly have*/
	UPROPERTY(EditAnywhere, Category = "Drop Weapons")
	TArray<TSubclassOf<class APickUpItem>> dropWeapons;

	/** The ID of the current held weapon*/
	int currentWeaponID;

	/**Server Function which will drop the current weapon*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDropWeapon();

	/**Unreal atribute of the camera component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* cameraComponent;

	/**Server function which will perform the acton of a rightmouse click*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerRightMouseClick();


public:

	/** Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called every frame*/
	virtual void Tick(float DeltaTime) override;

	/**Handles the movement forward and backwards of the player*/
	void MoveForward(float Value);

	/**Handles the movement sidewaysof the player*/
	void MoveRight(float Value);

	/**Server function called when the player leaves the game
	* Needs to be server function so that it will be synced over all devices
	*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerLeaveGame();

	/**Temporarly not used*/
	UFUNCTION()
		void DestroyPlayer();

	/**Makes sure the player dies when hp reaches zero */
	UFUNCTION()
		void UpdateLifeStatus();

	/** This method gives a player stamina and max stamina*/
	UFUNCTION()
		void EnergizePlayer(float amount);

	/**Used to gain power on the bow and drain the stamina
	* !!!! MAGIC NUMBER!!!!
	*/
	bool UpdateBowTension(float DeltaTime);

	/**is Called on the tick,
	 * Used to slowly gain energy
	 * !!!! MAGIC NUMBER!!!!
	 */
	void RegainEnergy(float DeltaTime);

	/**perform a raycast on the server, Used to mine things or pick things up
	* !!!! MAGIC NUMBER!!!!
	*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPerformMineCast();

	/**Called to handle melee combat on the server
	* !!!! MAGIC NUMBER!!!!
	*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerPerformHitCast();

	/**Serever function which will launch an arrow in the world
	* !!!! MAGIC NUMBER!!!!
	*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire();

	/*Sets all weapons invisible*/
	void WeaponVisibility();
	
	/** weaponSwitching */
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSlot1();
	/** weaponSwitching */
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSlot2();
	/** weaponSwitching */
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSlot3();
	/** weaponSwitching */
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSlot4();
	/** weaponSwitching */
	UFUNCTION(Server, Reliable, WithValidation)
		void WeaponSlot5();
	
	/**Charges a arrow when the bow is equiped and enough power is avaible */
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerDrawArrow();

	/**The weapon the player is wielding with its id */
	UPROPERTY(Replicated)
		int equipedWeapon;

	/**Bow is equiped on the player.
	 * Checked for the shot function
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bowEquiped;

	/**Check if a two handed weapon is equiped
	 * used in the animation
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool twoHanderEquiped;

};
