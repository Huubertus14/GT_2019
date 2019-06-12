// Fill out your copyright notice in the Description page of Project Settings.


#include "Woodcutter.h"
#include "UnrealNetwork.h"
#include "Engine.h"

// Sets default values
AWoodcutter::AWoodcutter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/WoodcutterHut/WoodcutterHut.WoodcutterHut'"));
	UStaticMesh* Asset = MeshAsset.Object; 

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	meshComponent->SetStaticMesh(Asset);
	
	meshComponent->SetWorldScale3D(FVector(17,17,17));
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AWoodcutter::BeginPlay()
{
	Super::BeginPlay();
	Spawn();
}

// Called every frame
void AWoodcutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWoodcutter::Spawn()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	FVector position = GetActorLocation();
	position.Z = 200;
	FRotator rotation = GetActorRotation();
	
	AWorker* newWorker = GetWorld()->SpawnActor<AWorker>(workerToCreate, position, rotation, spawnParams);
	newWorker->hutPosition = position;
}
void AWoodcutter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWoodcutter, workerToCreate);
}

