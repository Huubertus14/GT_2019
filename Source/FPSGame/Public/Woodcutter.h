// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Worker.h"
#include "Woodcutter.generated.h"

UCLASS()
class FPSGAME_API AWoodcutter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWoodcutter();
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* meshComponent;

	UPROPERTY(Replicated, EditAnywhere)
		TSubclassOf<AWorker> workerToCreate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Spawn();

};
