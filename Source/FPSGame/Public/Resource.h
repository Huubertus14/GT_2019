// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

UCLASS()
class FPSGAME_API AResource : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AResource();
	void AddAmount(int Number);
	void RemoveAmount(int Number);

	void ResetAmount();
	int GetAmount();
private:

	UPROPERTY(Replicated)
	int Amount = 0;

public:	

};
