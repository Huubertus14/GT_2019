// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

//! Holds the resource for the player
/*!
<deprecated>
This class is a single resource for the player and is stored in the world hidden for reusable reasons.
*/
UCLASS()
class FPSGAME_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	

	AResource();

	//! Add amound to the resource
	void AddAmount(int t_number);

	//! Used to remove an amount to a resource 
	void RemoveAmount(int t_number);

	//! Used to set a value of that resource to 0
	void ResetAmount();

	//!Returns the current value of that resource 
	int GetAmount();


private:
	//! Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//! The replicated amount of this resource for the server 
	UPROPERTY(Replicated)
		int m_r_amount;


	
};
