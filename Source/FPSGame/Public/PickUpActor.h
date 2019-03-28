// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourcePickUpTrigger.h"
#include "PickUpActor.generated.h"

UCLASS()
class FPSGAME_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

	UPROPERTY(EditAnywhere, Category = "ToSpawn")
	TSubclassOf<class AResourcePickUpTrigger> GroundActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Respawn();

public:	


};
