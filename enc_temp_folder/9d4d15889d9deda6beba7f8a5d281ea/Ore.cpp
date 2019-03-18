// Fill out your copyright notice in the Description page of Project Settings.

#include "Ore.h"

// Sets default values
AOre::AOre()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Life = 100;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MeshComp->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Called when the game starts or when spawned
void AOre::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AOre::OreDirection(FVector hitPoint) {
	FVector CenterPoint = GetActorLocation();
	FVector OutDirection = hitPoint - CenterPoint;
	return OutDirection;
}

void AOre::OreHitSpawn(FVector hitPoint) {
	OreDirection(hitPoint);
	Life--;
	if (Life <= 0) {
		Destroy();
		//Needs server validation.
	}
}

