// Fill out your copyright notice in the Description page of Project Settings.

#include "testPawn.h"
#include "Arrow.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
// Sets default values
AtestPawn::AtestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-20, -5,20));
	OurCamera->SetRelativeRotation(FRotator(0,0,0));

	OurVisibleComponent->SetupAttachment(RootComponent);

	power = 0;
}

// Called when the game starts or when spawned
void AtestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;

		if (bGrowing) {
			//CurrentScale += DeltaTime;
		}
		else {
			//CurrentScale -= (DeltaTime *.5);
		}
		if(isDrawn) {
			power += .2f;
		}
		else {
			power = 0;
		}
		FString TheFloatStr = FString::SanitizeFloat(power);
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, *TheFloatStr);
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

		{
			if (!CurrentVelocity.IsZero()) {
				FVector newLocation = GetActorLocation()+(CurrentVelocity * DeltaTime);
				SetActorLocation(newLocation);
			}
		}
	}
	spawnTime--;

}

// Called to bind functionality to input
void AtestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Grow",IE_Pressed,this, &AtestPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AtestPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AtestPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AtestPawn::Move_YAxis);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AtestPawn::DrawArrow);
	InputComponent->BindAction("Fire", IE_Released, this, &AtestPawn::FireArrow);

	InputComponent->BindAxis("Turn", this, &AtestPawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AtestPawn::AddControllerPitchInput);

}

void AtestPawn::StartGrowing()
{
	bGrowing = true;
}

void AtestPawn::StopGrowing()
{
	bGrowing = false;
}

void AtestPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f,1.0f)*100;
}

void AtestPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100;
}

void AtestPawn::DrawArrow()
{
	isDrawn = true;
}

void AtestPawn::FireArrow()
{
	FVector location = GetActorLocation();
	location.Z = 2;
	SetActorLocation(location);

	
	FVector pos = GetActorLocation();
	FRotator rot = GetActorRotation();
	pos.Z += 20;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	if (spawnTime < 0) {
		AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), pos, rot, spawnParams);
		newArrow->speed = power;
		spawnTime = 60;
		power = 0;
	}
	isDrawn = false;
}