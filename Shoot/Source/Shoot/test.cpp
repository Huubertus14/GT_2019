// Fill out your copyright notice in the Description page of Project Settings.

#include "test.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Atest::Atest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnTime = 60;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_arrow(TEXT("StaticMesh'/Game/StarterContent/Models/Bow/Bow_pCube1.Bow_pCube1'"));
	UStaticMesh* Asset = StaticMeshOb_arrow.Object;
	mesh->SetStaticMesh(Asset);
}

// Called when the game starts or when spawned
void Atest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	location.Z = 2;
	SetActorLocation(location);

	spawnTime--;
	FVector pos = GetActorLocation();
	FRotator rot = GetActorRotation();
	pos.Z += 8;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	if (spawnTime < 0) {
		AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), pos, rot, spawnParams);
		
		spawnTime = 60;
	}
}

