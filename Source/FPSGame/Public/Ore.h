// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcePickUpTrigger.h"
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

public:	


	FVector OreDirection(FVector hitPoint);

	UFUNCTION()
	void OreHitSpawn(FVector hitPoint);

	UFUNCTION()
		void OreEmpty();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "ToSpawn")
	TSubclassOf<class AResourcePickUpTrigger> PickUpItem;

	UPROPERTY(EditAnywhere, Category = "Resource")
		int resourceID;

	UPROPERTY(EditAnywhere, Category = "Resource")
		int resourceAmount;

	UPROPERTY()
		int Life;


};
