// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPickAxe.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSPickAxe::AFPSPickAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AxeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMeshComp"));
	RootComponent = AxeMeshComp;
}

// Called when the game starts or when spawned
void AFPSPickAxe::BeginPlay()
{
	Super::BeginPlay();

}

void AFPSPickAxe::Cut()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 100);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;

		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams)) {

		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
	}
}

// Called every frame
void AFPSPickAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


