// Fill out your copyright notice in the Description page of Project Settings.

#include "Ore.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))
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
	//SetReplicateMovement(true);
	
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
	/*SetOwner(character);
	
	print("---Ore hit---");
	OreServerSpawn();
	OreServerDestroy();
	print("---Done Hit---");*/
	if (Role < ROLE_Authority)
	{
		OreServerSpawn();
		return;
	}
	FVector outwardVector = OreDirection(HitPoint);
	outwardVector.Normalize(1.f);
	if (PickUpItem) {

		print("/Pick up item called");
		//UWorld* world = GetWorld();
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		//spawnParams.Owner = this;
		FRotator rotator = FRotator(0.f, 0.f, 0.f);
		FVector spawnLocation = outwardVector + HitPoint;

		GetWorld()->SpawnActor<AResourcePickUpTrigger>(PickUpItem, spawnLocation, rotator, spawnParams);
		print("/Item created");
		Life--;
		if (Life <= 0) {
			print("/Source destroy");
			Destroy();
			//Needs server validation.
		}
	}
}


void AOre::OreServerDestroy_Implementation()
{
	Life--;
	if (Life <= 0) {
		Destroy();
		//Needs server validation.
	}
}

bool AOre::OreServerDestroy_Validate()
{
	return true;
}

void AOre::OreServerSpawn_Implementation()
{
	print("Server Call");
	OreHitSpawn(HitPoint);
}

bool AOre::OreServerSpawn_Validate()
{
	print("/Spawn Validated");
	return true;
}

