// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "ResourcePickUpTrigger.generated.h"

class UShapeComponent;
//! The resource which can be picked up
/*!
 *This class will hold al the info for a resource which can be picked up by a player and spawned by a ore
 **/
UCLASS()
class FPSGAME_API AResourcePickUpTrigger : public ATriggerSphere
{
	GENERATED_BODY()

public:

	AResourcePickUpTrigger();
	
	void BeginPlay();

	/**This function is called whenever there is an collision with another actor
	 *This function is always replicated */
	UFUNCTION()
	void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);

	/** The mesh component of this BP */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	/**The resource ID */
	UPROPERTY(EditAnywhere, Category = "Resource")
	int resourceID;

	/**The resource amount */
	UPROPERTY(EditAnywhere, Category = "Resource")
	int resourceAmount;
	
};
