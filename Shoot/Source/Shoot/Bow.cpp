// Fill out your copyright notice in the Description page of Project Settings.

#include "Bow.h"
#include "Arrow.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
// Sets default values
ABow::ABow()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-20, -10, 20));
	OurCamera->SetRelativeRotation(FRotator(0, 0, 0));
	OurCamera->bUsePawnControlRotation = true;
	OurVisibleComponent->SetupAttachment(RootComponent);

	spawnTime = 60;
	isPressed = false;
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{

		if (isDrawn) {
			power += .5f;
		}
		else {
			power = 0;
		}
		if (!CurrentVelocity.IsZero() && isPressed) {
			FVector newLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(newLocation);
		}
		spawnTime--;
		CurrentVelocity = CurrentVelocity * .3;
	}
}

// Called to bind functionality to input
void ABow::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &ABow::MoveForward);
	InputComponent->BindAxis("MoveY", this, &ABow::MoveRight);
	InputComponent->BindAxis("Turn", this, &ABow::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ABow::AddControllerPitchInput);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABow::DrawArrow);
	InputComponent->BindAction("Fire", IE_Released, this, &ABow::FireArrow);
}

void ABow::MoveForward(float Val)
{
	FVector f =GetActorForwardVector();
	if ((Controller != NULL) && (Val != 0.0f))
	{
		CurrentVelocity = (f * 100)*Val;
		isPressed = true;
	}
	else {
		//isPressed = false;
	}
}

void ABow::MoveRight(float Val)
{
	FVector f = GetActorForwardVector();
	if ((Controller != NULL) && (Val != 0.0f))
	{
		
		
		//CurrentVelocity = (f * 100)*Val;
		//isPressed = true;
	}
	else {
		//isPressed = false;
	}

}

void ABow::DrawArrow()
{
	isDrawn = true;
}

void ABow::FireArrow()
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

