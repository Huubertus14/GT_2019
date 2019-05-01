#include "Arrow.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AArrow::AArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//mesh
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

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();

}

void AArrow::ServerMovement_Implementation(FVector _pos, FRotator _rot)
{
	SetActorLocationAndRotation(_pos, _rot);
}

bool AArrow::ServerMovement_Validate(FVector _pos, FRotator _rot)
{
	return true;
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetVelocity() != FVector(0.f,0.f,0.f)) {
		FVector dir = GetVelocity();
		FRotator rot = FRotationMatrix::MakeFromX(dir).Rotator();
		SetActorRotation(rot);

	}
	m_lifeSpan--;
	if (m_lifeSpan < 0) {
		Destroy();
	}

}

void AArrow::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		meshComponent->SetSimulatePhysics(false);

		APlayerCharacter* charHit = Cast<APlayerCharacter>(OtherActor);

		if (charHit) {

			if (charHit->Role = ROLE_Authority)
			{
				UE_LOG(LogTemp, Warning, TEXT("Play who hit is server"));
			}

			//UE_LOG(LogTemp, Warning, TEXT("Player Hit"));
			charHit->HitPlayer(20); 
			
		}

		if (Role == ROLE_Authority)
		{
			//server things
			Destroy();
		}

	}
	else
	{
		if (Role == ROLE_Authority)
		{
			//server things
			Destroy();
		}

	}
}