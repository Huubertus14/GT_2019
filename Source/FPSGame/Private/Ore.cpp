// Fill out your copyright notice in the Description page of Project Settings.
#include "Ore.h"
#include "UnrealNetwork.h"

// Sets default values
AOre::AOre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_life =  FMath::RandRange(13, 25);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = meshComp;
	meshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

	
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
}

FVector AOre::OreDirection(FVector t_hitPoint) 
{
	FVector centerPoint = GetActorLocation();
	FVector outDirection = t_hitPoint - centerPoint;
	return outDirection;
}

void AOre::OreHitSpawn(FVector t_hitPoint) 
{
	if (Role == ROLE_Authority) {
		FVector outwardVector = OreDirection(t_hitPoint);
		outwardVector.Normalize(1.f);
		m_life--;
		if (pickUpItem) {

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			FRotator rotator = FRotator(0.f, 0.f, 0.f);
			FVector spawnLocation = t_hitPoint + outwardVector*5.f;

			AResourcePickUpTrigger* newPickup = GetWorld()->SpawnActor<AResourcePickUpTrigger>(pickUpItem, spawnLocation, rotator ,spawnParams);
			if (newPickup) 
			{
				UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(newPickup->GetRootComponent());
				if (meshComp) 
				{
					meshComp->AddForce(35000.f*meshComp->GetMass()*outwardVector);
				}
			}
		}

		if (m_life <= 0)
		{
			Destroy();
		}
	}
}

void AOre::OreEmpty()
{
	if (Role == ROLE_Authority) {
		m_life--;
		if(m_life <= 0)
		{
			Destroy();
		}
	}

}



