// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcePickUpTrigger.h"
#include "PlayerCharacter.h"

#include "Ore.generated.h"

UCLASS()
class FPSGAME_API AOre : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOre();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int Life;
	FVector HitPoint;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FVector OreDirection(FVector hitPoint);

	UFUNCTION()
		void OreHitSpawn(FVector hitPoint);

	UFUNCTION(Server, Reliable, WithValidation)
		void OreServerSpawn();

	UFUNCTION(Server, Reliable, WithValidation)
		void OreServerDestroy();

	UPROPERTY(EditAnywhere, Category = "ToSpawn")
		TSubclassOf<AResourcePickUpTrigger> PickUpItem;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

};
