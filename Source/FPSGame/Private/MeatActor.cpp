// Fill out your copyright notice in the Description page of Project Settings.

#include "MeatActor.h"

// Sets default values
AMeatActor::AMeatActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("MainMesh");
	mesh->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AMeatActor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
}

// Called every frame
void AMeatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeatActor::EatMeat()
{
	Destroy();
}

