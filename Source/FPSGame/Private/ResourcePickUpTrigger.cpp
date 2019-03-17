// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcePickUpTrigger.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))



AResourcePickUpTrigger::AResourcePickUpTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AResourcePickUpTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AResourcePickUpTrigger::OnOverlapEnd);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	
	UShapeComponent* newColl = GetCollisionComponent();
	newColl->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}


// Called when the game starts or when spawned
void AResourcePickUpTrigger::BeginPlay()
{
	Super::BeginPlay();

}


void AResourcePickUpTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// check if Actors do not equal nullptr and that 
	if (OtherActor && (OtherActor != this)) {
		// print to screen using above defined method when actor enters trigger box
		print("Overlap Begin");
		printFString("Overlapped Actor = %s", *OverlappedActor->GetName());
	}
}

void AResourcePickUpTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		// print to screen using above defined method when actor leaves trigger box
		print("Overlap Ended");
		printFString("%s has left the Trigger Box", *OtherActor->GetName());
	}
}

// Called every frame
void AResourcePickUpTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

