// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"

UCLASS()
class FPSGAME_API APickUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int weaponID;

public:	

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;

	//Called when you pick up the item
	void Pickup();

	//Get the item ID
	int GetID();

};
