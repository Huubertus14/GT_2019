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
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;
	mesh->SetSimulatePhysics(true);
	mesh->SetNotifyRigidBodyCollision(true);
	mesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	mesh->OnComponentHit.AddDynamic(this, &AArrow::OnCompHit);

	location = GetActorLocation();
	forward = 0;
	speed = 60;
	gravity = .1;
	lifeSpan = 300;

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
	lifeSpan--;
	if (lifeSpan < 0) {
		Destroy();
	}

}

void AArrow::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		mesh->SetSimulatePhysics(false);

		APlayerCharacter* charHit = Cast<APlayerCharacter>(OtherActor);

		if (charHit) {

			if (charHit->Role = ROLE_Authority)
			{
				UE_LOG(LogTemp, Warning, TEXT("Play who hit is server"));
			}

			//UE_LOG(LogTemp, Warning, TEXT("Player Hit"));
			charHit->life -= 40;
			if (charHit->life <= 0) {

				if (charHit->IsLocallyControlled())
				{
					//UE_LOG(LogTemp, Warning, TEXT("Player Die"));
					charHit->DestroyPlayer();
				}

			}
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