// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Bear.h"
#include "Components/StaticMeshComponent.h"

#define NO_TIME_OUT -1.0
#define TIME_OUT_ATTACKING 2.0

// Sets default values
AAI_Bear::AAI_Bear()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MeshComp->SetSimulatePhysics(true);
	MeshComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");

	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void AAI_Bear::BeginPlay()
{
	Super::BeginPlay();

	location = GetActorLocation();
	speed = 20;
	life = 300;

	currentState = BE_WALK;
}

// Called every frame
void AAI_Bear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAI_Bear::ChangeState(int nextState, float TO)
{
	currentState = nextState;
	tOut = CurrentTime() + TO;
}

void AAI_Bear::Thinking()
{
	switch (currentState)
	{
		case BE_WALK:

			Walk();

			break;

		case BE_RUN:
			break;

		case BE_ATTACK:
			break;

		case BE_DIE:
			break;

	default:
		break;
	}
}

void AAI_Bear::Walk()
{

}

void AAI_Bear::Run()
{
	
}

void AAI_Bear::Attack()
{
}

void AAI_Bear::Die()
{
}

double AAI_Bear::CurrentTime()
{
	return 0.0f;
}

float AAI_Bear::GetCurrentTime()
{
	return 0.0f;
}

bool AAI_Bear::TimeOut()
{
	return tOut < CurrentTime();
}

