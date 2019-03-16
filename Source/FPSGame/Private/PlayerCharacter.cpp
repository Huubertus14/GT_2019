// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	//Finds the resource bp.
	static ConstructorHelpers::FClassFinder<AResource> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Resource"));
	toCreate = PlayerPawnClassFinder.Class;

	for (int i = 0; i < 3; i++)
	{
		//creates 3 resources for this player.
		if (Spawn()) {
			UE_LOG(LogTemp, Warning, TEXT("Made a Resource"));
		}
	}

	//Adds a small amount to resource 0
	if (Resources.Num() > 0) {
		Resources[0]->AddAmount(10);
		UE_LOG(LogTemp, Warning, TEXT("Total amount of cash: %i"), Resources[0]->GetAmount());
	}

	UE_LOG(LogTemp, Warning, TEXT("Total amount of Resources: %i"), Resources.Num());
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;
 	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);

	}
}

bool APlayerCharacter::Spawn() {
	if (toCreate) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator = FRotator(0,0,0);
			FVector spawnLocation = FVector(0,0,0);
			Resources.Emplace(world->SpawnActor<AResource>(toCreate, spawnLocation, rotator, spawnParams));
			return true;
		}
	}
	return false;
}