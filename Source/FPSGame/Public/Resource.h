// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

//!Holds all info a resource needs
/*!
 *A basic data class to hold all info a resource needs
 */
UCLASS()
class FPSGAME_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Sets default values for this actor's properties*/
	AResource();

	//! Add amound to the resource
	void AddAmount(int Number);

	//! Used to remove an amount to a resource 
	void RemoveAmount(int Number);

	//! Used to set a value of that resource to 0
	void ResetAmount();

	//!Returns the current value of that resource 
	int GetAmount();

	//!The replicated amount of this resource for the server 
	UPROPERTY(Replicated)
	int Amount;

private:


	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
