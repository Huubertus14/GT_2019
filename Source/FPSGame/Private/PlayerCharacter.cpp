// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "Ore.h"
#include "Arrow.h"

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

	SetReplicates(true);

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::PerformMineCast);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::DrawArrow);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::FireArrow);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::ServerFire_Implementation()
{
	FVector pos = GetActorLocation();
	FRotator rot = GetActorRotation();
	FVector f = GetActorForwardVector();
	FRotator camera = CameraComponent->GetComponentRotation();

	pos.X += f.X * 100;
	pos.Y += f.Y * 100;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	if (spawnTime < 0) {
		AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), pos, camera, spawnParams);
		newArrow->speed = power;
		spawnTime = 60;
		power = 0;
	}
	isDrawn = false;
}

bool APlayerCharacter::ServerFire_Validate()
{
	return true;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (!IsLocallyControlled())
		{
			arrowRotation = CameraComponent->RelativeRotation;
			arrowRotation.Pitch = RemoteViewPitch * 360.0f / 255.0f; // convert to right Uint8

			CameraComponent->SetRelativeRotation(arrowRotation);
		}
		if (isDrawn) {
			power += .5f;
		}
		else {
			power = 0;
		}
		spawnTime--;
	}

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

void APlayerCharacter::PerformMineCast() {
	FVector StartTrace = GetActorLocation();
	FHitResult* HitResult = new FHitResult();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector EndTrace = StartTrace + (ForwardVector * 1000.f);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)) {
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true, 5.f);
		FString temp = HitResult->Location.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp);
		//Cast from hitResult to if possible Ore.
		AOre* hitTemp = Cast<AOre>(HitResult->Actor);
		if (hitTemp) {
			hitTemp->OreHitSpawn(HitResult->Location);
			FString temp2 = "Ore";
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp2);
		}
	}
	
}

void APlayerCharacter::DrawArrow()
{
	isDrawn = true;
}

void APlayerCharacter::FireArrow()
{
	ServerFire();
	
	UE_LOG(LogTemp, Warning, TEXT("arrow"));
}