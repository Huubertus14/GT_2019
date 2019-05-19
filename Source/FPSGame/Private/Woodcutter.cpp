// Fill out your copyright notice in the Description page of Project Settings.

#include "Woodcutter.h"

// Sets default values
AWoodcutter::AWoodcutter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AWoodcutter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWoodcutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

