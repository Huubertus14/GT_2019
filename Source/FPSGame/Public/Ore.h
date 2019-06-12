// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Yeet

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcePickUpTrigger.h"
#include "Ore.generated.h"

//! The class of an farmable resource
/*!
 This class has all the functions to make an farmable resource work.
Most of the values are set in the BP of this class
*/
UCLASS()
class FPSGAME_API AOre : public AActor
{
	GENERATED_BODY()

public:
	/** Sets default values for this actor's properties */
	AOre();

protected:
	/** Called when the game starts or when spawned*/
	virtual void BeginPlay() override;

private:
	/**The amount of resources this ore can spawn */
	UPROPERTY()
		int m_life;

	/**The ID of this resource */
	UPROPERTY(EditAnywhere, Category = "Resource")
		int m_resourceID;

	/**The amount the of the resource is given out*/
	UPROPERTY(EditAnywhere, Category = "Resource")
		int m_resourceAmount;

public:
	/** resourcesID accessor */
	UFUNCTION()
		int GetResourceID();
	/** resourcesAmount accessor */
	UFUNCTION()
		int GetResourceAmount();

	/**De direction the ore needs to spawn in*/
	UFUNCTION()
		FVector OreDirection(FVector t_hitPoint);

	/** The point where the player hits the object*/
	UFUNCTION()
		void OreHitSpawn(FVector t_hitPoint);

	/** A check if the ore is empty 
	 * If so the ore will destroy itself in this method
	 */
	UFUNCTION()
		void OreEmpty();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComp;

	/**The actor which is spawned when the ore is hit
	 *Is set in the BP of this object */
	UPROPERTY(EditAnywhere, Category = "ToSpawn")
		TSubclassOf<class AResourcePickUpTrigger> pickUpItem;
};
