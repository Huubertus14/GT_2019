// Fill out your copyright notice in the Description page of Project Settings.

#include "NewOre.h"

// Sets default values
ANewOre::ANewOre()
{
	
	m_life = 100;
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = meshComp;
	meshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

}

FVector ANewOre::OreDirection(FVector t_hitPoint)
{
	FVector centerPoint = GetActorLocation();
	FVector outDirection = t_hitPoint - centerPoint;
	return outDirection;
}

void ANewOre::ServerSpawn_Implementation(FVector t_hitPoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Ore spawn uitgevoerd"));
	FVector outwardVector = OreDirection(t_hitPoint);
	outwardVector.Normalize(1.f);
	m_life--;
	if (PickUpItem) {
		UE_LOG(LogTemp, Warning, TEXT("Spawn Item!"));
		UWorld* world = GetWorld();
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		FRotator rotator = FRotator(0.f, 0.f, 0.f);
		FVector spawnLocation = outwardVector + t_hitPoint;
		world->SpawnActor<AResourcePickUpTrigger>(PickUpItem, spawnLocation, rotator, spawnParams);

	}
	if (m_life <= 0) {
		Destroy();
	}
}

bool ANewOre::ServerSpawn_Validate(FVector t_hitPoint)
{
	return true;
}


