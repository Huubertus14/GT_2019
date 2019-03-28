// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpActor.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	

	if (Role == ROLE_Authority) {
		Respawn();
	}
}


void APickUpActor::Respawn()
{
	if (GroundActor) 
	{
		print("Check your blueprint for GroundActor");
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//Spawn The actor
	GetWorld()->SpawnActor<AResourcePickUpTrigger>(GroundActor, GetTransform(), SpawnParams);
}

