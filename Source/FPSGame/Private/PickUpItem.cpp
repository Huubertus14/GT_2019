// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My_Pickup_Mesh"));
	MyMesh->SetSimulatePhysics(true);
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUpItem::Pickup()
{
	Destroy();
}

int APickUpItem::GetID()
{
	return weaponID;
}



