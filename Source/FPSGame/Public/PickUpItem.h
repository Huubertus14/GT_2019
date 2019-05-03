// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"

//! The class of an object which the player can pickup
/*!
 *This class holds all the infor and functions of an object which can be picked up by a player
 *Like weapons etc.
 **/
UCLASS()
class FPSGAME_API APickUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties*/
	APickUpItem();

	/**The mesh component of the PickupItem
	 *Is set in the BP */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* MeshPickupItem;

	/**Called when you pick up the item
	Will destroy the actor*/
	void Pickup();

	/**Returns the weapon ID*/
	int GetWeaponID();


protected:
	/** Called when the game starts or when spawned*/
	virtual void BeginPlay() override;

	/**The ID of a weapon
	 *Is set in the BP and will depend which item 
	 *the player gets in their invertory */
	UPROPERTY(EditAnywhere, Category = "Weapon")
		int weaponID;
	
};
