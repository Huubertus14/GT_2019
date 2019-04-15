// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkCube.h"
#include "UnrealNetwork.h"
#include "Engine.h"

// Sets default values
ANetworkCube::ANetworkCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
}

// Called when the game starts or when spawned
void ANetworkCube::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called every frame
void ANetworkCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Role == ROLE_Authority) {
		//FRotator newRot = CameraComponent->RelativeRotation;
		//newRot.Pitch = RemoteViewPitch * 360.0f / 255.0f;
			
		//CameraComponent->SetRelativeRotation(newRot);
	}

}

