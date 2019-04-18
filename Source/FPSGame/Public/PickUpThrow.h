// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "PickUpThrow.generated.h"

UCLASS()
class FPSGAME_API APickUpThrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpThrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;

	UFUNCTION()
	void Pickup();

	bool bHolding;
	bool bGravity;
 
	ACharacter* MyCharacter;
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

};
