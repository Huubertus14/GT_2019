// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "ResourcePickUpTrigger.generated.h"

/**
 * 
 */
class UShapeComponent;
UCLASS()
class FPSGAME_API AResourcePickUpTrigger : public ATriggerSphere
{
	GENERATED_BODY()

public:

	// constructor sets default values for this actor's properties
	AResourcePickUpTrigger();
	
	void BeginPlay();
	
	UFUNCTION()
	void OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor);


	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	
};
