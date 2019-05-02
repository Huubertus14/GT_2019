// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeatActor.generated.h"

//! The functions of meat
/*!
 *Holds all the function meat should have
 *May be change later to some other class, Or the Pickup class
 **/

UCLASS()
class FPSGAME_API AMeatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Sets default values for this actor's properties*/
	AMeatActor();

protected:
	/** Called when the game starts or when spawned*/
	virtual void BeginPlay() override;

	/**The mesh component of this BP
	 *Is set in the BP */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

public:
	/** Is Called when the meat is eaten
	 *Will destroy in this function */
	void EatMeat();

};
