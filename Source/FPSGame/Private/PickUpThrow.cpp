// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpThrow.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
APickUpThrow::APickUpThrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My_Pickup_Mesh"));
	MyMesh->SetSimulatePhysics(true);
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void APickUpThrow::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);

}

void APickUpThrow::Pickup() {
	Destroy();
}

int APickUpThrow::GetID()
{
	return weaponID;
}


