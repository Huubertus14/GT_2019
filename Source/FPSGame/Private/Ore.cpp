// Fill out your copyright notice in the Description page of Project Settings.
#include "Ore.h"
#include "UnrealNetwork.h"

// Sets default values
AOre::AOre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Life = FMath::RandRange(5,11);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AOre::OreDirection(FVector hitPoint) 
{
	FVector CenterPoint = GetActorLocation();
	FVector OutDirection = hitPoint - CenterPoint;
	return OutDirection;
}

void AOre::OreHitSpawn(FVector hitPoint) 
{
	if (Role == ROLE_Authority) {
		FVector outwardVector = hitPoint;
		outwardVector.Normalize(1.f);
		Life--;
		if (PickUpItem) {

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			FRotator rotator = FRotator(0.f, 0.f, 0.f);
			FVector spawnLocation = hitPoint;
			GetWorld()->SpawnActor<AResourcePickUpTrigger>(PickUpItem, spawnLocation, rotator ,spawnParams);
		}

		if (Life <= 0)
		{
			Destroy();
		}
	}
}

