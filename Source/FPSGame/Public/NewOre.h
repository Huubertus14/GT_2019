// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ResourcePickUpTrigger.h"
#include "NewOre.generated.h"

//! Obsolete?
UCLASS()
class FPSGAME_API ANewOre : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANewOre();

private:
	int m_life;

public:
	FVector OreDirection(FVector t_hitPoint);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawn(FVector t_hitPoint);

	UPROPERTY(EditAnywhere, Category = "ToSpawn")
		TSubclassOf<class AResourcePickUpTrigger> PickUpItem;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComp;

};
