// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcePickUpTrigger.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))



AResourcePickUpTrigger::AResourcePickUpTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AResourcePickUpTrigger::OnOverlapBegin);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	
	UShapeComponent* newColl = GetCollisionComponent();
	newColl->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SetReplicates(true);
	SetReplicateMovement(true);
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
		APlayerCharacter* tempPlayer = Cast<APlayerCharacter>(OtherActor);
		if (tempPlayer) {
			if (Role = ROLE_Authority) {
				tempPlayer->Resources[1]->AddAmount(10);
				Destroy();
			}
		}
	}
}


