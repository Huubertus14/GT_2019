// Fill out your copyright notice in the Description page of Project Settings.

#include "MeatActor.h"

// Sets default values
AMeatActor::AMeatActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AMeatActor::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
}


void AMeatActor::EatMeat()
{
	//Destroys the meat actor
	Destroy();
}

