// Fill out your copyright notice in the Description page of Project Settings.

#include "Worker.h"
#include "Engine.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/character.character'"));
	UStaticMesh* Asset = MeshAsset.Object;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	meshComponent->SetStaticMesh(Asset);

	meshComponent->SetWorldScale3D(FVector(1, 1, 1));

	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

