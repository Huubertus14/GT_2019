// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSPickAxe.generated.h"

UCLASS()
class FPSGAME_API AFPSPickAxe : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSPickAxe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponents")
		USkeletalMeshComponent* AxeMeshComp;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Cut();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};