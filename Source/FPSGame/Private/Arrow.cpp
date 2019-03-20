#include "Arrow.h"
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
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_arrow(TEXT("StaticMesh'/Game/Models/Arrow/Arrow.Arrow'"));
	UStaticMesh* Asset = StaticMeshOb_arrow.Object;
	mesh->SetStaticMesh(Asset);
	mesh->SetWorldScale3D(FVector(3, 3, 3));
	mesh->SetRelativeScale3D(FVector(3, 3, 3));
	mesh->SetSimulatePhysics(true);
	mesh->SetNotifyRigidBodyCollision(true);
	mesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	mesh->OnComponentHit.AddDynamic(this, &AArrow::OnCompHit);

	RootComponent = mesh;

	location = GetActorLocation();
	forward = 0;
	speed = 8;
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

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//forward += 1;
	//location.X = forward;
	speed = speed * 0.99;
	gravity = gravity * 1.04;
	FVector pos = GetActorLocation();
	FVector f = GetActorForwardVector();
	pos += f * speed;
	//pos.Z -= gravity;
	FRotator rot = GetActorRotation();
	rot.Pitch -= gravity / 4;
	//SetActorLocation(pos);
	SetActorLocationAndRotation(pos, rot);


	lifeSpan--;
	if (lifeSpan < 0) {
		Destroy();
	}

}

void AArrow::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine && (OtherActor->GetName() != "Plane_2"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I just hit: %s"), *OtherActor->GetName()));
		}

		gravity = 0;
		speed = 0;
		FString s = "Target";
		if (OtherActor->GetName() == s) {
			mesh->SetSimulatePhysics(false);
		}



	}
}