#include "Arrow.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

AArrow::AArrow()
{

	PrimaryActorTick.bCanEverTick = true;
	
	//mesh settings
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = meshComponent;
	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetNotifyRigidBodyCollision(true);
	meshComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	meshComponent->OnComponentHit.AddDynamic(this, &AArrow::OnCompHit);

	m_lifeSpan = 300;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Update the rotation of the arrow towards its direction
	if (GetVelocity() != FVector(0.f,0.f,0.f)) {
		FVector dir = GetVelocity();
		FRotator rot = FRotationMatrix::MakeFromX(dir).Rotator();
		SetActorRotation(rot);

	}

	//Destroy after its time on earth is done.
	m_lifeSpan-= DeltaTime;
	if (m_lifeSpan <= 0) {
		Destroy();
	}

}

void AArrow::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	//if the arrow hits a player deal some damage
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		APlayerCharacter* charHit = Cast<APlayerCharacter>(OtherActor);

		if (charHit) 
		{
			charHit->HitPlayer(arrowDamage); 
		}
	}

	//After hitting anything the arrow gets destroyed
	if (Role == ROLE_Authority)
	{
		Destroy();
	}
}