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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int Life;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector OreDirection(FVector hitPoint);
	void OreHitSpawn(FVector hitPoint);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawn(FVector hitPoint);

	UPROPERTY(EditAnywhere, Category = "ToSpawn")
		TSubclassOf<class AResourcePickUpTrigger> PickUpItem;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

};
