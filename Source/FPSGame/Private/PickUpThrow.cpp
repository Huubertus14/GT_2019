// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpThrow.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
APickUpThrow::APickUpThrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My_Pickup_Mesh"));
	MyMesh->SetSimulatePhysics(true);
	RootComponent = MyMesh;

	//bHolding = false;
	//bGravity = true;

	//UE_LOG(LogTemp, Warning, TEXT("Holding things done!!!!!!!!!!!!!!!!!")); 
	//weaponID = 2;
}

// Called when the game starts or when spawned
void APickUpThrow::BeginPlay()
{
	Super::BeginPlay();

	//MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	//PlayerCamera = MyCharacter->FindComponentByClass<UCameraComponent>();

	//TArray<USceneComponent*> components;

	//MyCharacter->GetComponents(components);

//	if (components.Num() > 0) 
//	{
//		for (auto& comp : components) 
//		{
//			if(comp->GetName() == "HoldingComponent")
//			{
//				HoldingComp = Cast<USceneComponent>(comp);
//			}
//		}
//
//	}
//
}

void APickUpThrow::Pickup() {
	Destroy();
}

int APickUpThrow::GetID()
{
	return weaponID;
}

// Called every frame
void APickUpThrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(bHolding && HoldingComp)
	//{
	//	SetActorLocationAndRotation(HoldingComp->GetComponentLocation(), HoldingComp->GetComponentRotation());
	//}

}
//
//void APickUpThrow::Pickup()
//{
//	
//
//	bHolding = !bHolding;
//	bGravity = !bGravity;
//	MyMesh->SetEnableGravity(bGravity);
//	MyMesh->SetSimulatePhysics(bHolding ? false : true);
//	MyMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
//
//	if (!bHolding) 
//	{
//		ForwardVector = PlayerCamera->GetForwardVector();
//		MyMesh->AddForce(ForwardVector * 100000 * MyMesh->GetMass());
//	}
//}
//
