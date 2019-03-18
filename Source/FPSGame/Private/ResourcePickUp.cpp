// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcePickUp.h"
#include "Components//StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AResourcePickUp::AResourcePickUp()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	ShpereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	ShpereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AResourcePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourcePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

