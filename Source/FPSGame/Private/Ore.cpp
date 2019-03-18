// Fill out your copyright notice in the Description page of Project Settings.

#include "Ore.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AOre::AOre()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Life = 10;
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
	HitPoint = hitPoint;
	OreServerSpawn();
}

void AOre::OreServerSpawn_Implementation()
{
	FVector outwardVector = OreDirection(HitPoint);
	outwardVector.Normalize(1.f);
	Life--;
	if (PickUpItem) {
		UWorld* world = GetWorld();
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		FRotator rotator = FRotator(0.f, 0.f, 0.f);
		FVector spawnLocation = outwardVector + HitPoint;

		world->SpawnActor<AResourcePickUpTrigger>(PickUpItem, spawnLocation, rotator, spawnParams);

	}
	if (Life <= 0) {
		Destroy();
		//Needs server validation.
	}
}

bool AOre::OreServerSpawn_Validate()
{
	return true;
}

