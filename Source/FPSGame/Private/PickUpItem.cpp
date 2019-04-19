// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

/*
All weapons will have an ID which the player knows. Depending on this ID the player knows which weapon it is wielding and which weapon it needs to drop.
The ID's are as following:
	1 = Sword
	2 = 2H Sword
	3 = dagger
*/

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



