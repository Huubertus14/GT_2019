// Fill out your copyright notice in the Description page of Project Settings.

#include "Worker.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Engine.h"

// Sets default values
AWorker::AWorker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh"));

	meshComponent->BodyInstance.bLockXRotation = true;
	meshComponent->BodyInstance.bLockYRotation = true;

	gather = true;

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
	float speed = 5;
	Super::Tick(DeltaTime);
	FVector loc = GetActorLocation();

	if (gather)
	{
		float xX = -832.1;
		float yY = -1498.8;
		float zZ = 148.4;
		FVector f = FVector(xX, yY, zZ);

		float dx = f.X - loc.X;
		float dy = f.Y - loc.Y;
		float length = FGenericPlatformMath::Sqrt(dx*dx + dy * dy);
		dx /= length;
		dy /= length;
		dx *= speed;
		dy *= speed;
		loc.X += dx;
		loc.Y += dy;


		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(loc, f);
		Rot.Yaw -= 90;
		SetActorRotation(Rot);
		float distance = FVector::Distance(f, loc);
		if (distance < 400)
			gather = false;
		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
	}
	else
	{
		float dx = hutPosition.X - loc.X;
		float dy = hutPosition.Y - loc.Y;
		float length = FGenericPlatformMath::Sqrt(dx*dx + dy * dy);
		dx /= length;
		dy /= length;
		dx *= speed;
		dy *= speed;
		loc.X += dx;
		loc.Y += dy;
		//SetActorLocation(loc);
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(loc, hutPosition);
		Rot.Yaw -= 90;
		SetActorRotation(Rot);
		float distance = FVector::Distance(hutPosition, loc);
		if (distance < 500)
			gather = true;
		//UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
	}
	SetActorLocation(loc);



}

